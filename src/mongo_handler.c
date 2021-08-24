/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mongo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:34:02 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 10:59:04 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

extern t_api		source;
t_mongo				mongo;

/*Verifica se há, ou não um usuário no banco de dados*/
static int	db_query()
{
	mongoc_cursor_t		*cursor;
	bson_t				*query;
	bson_t				*bson;
	bson_oid_t			*temp;
	bson_iter_t			iter;
	bson_iter_t			id;

	query = bson_new();
	BSON_APPEND_UTF8(query, "login", source.user);
	cursor = mongoc_collection_find_with_opts(mongo.collection, query, NULL, NULL);
	if (mongoc_cursor_next(cursor, (const bson_t **)&bson))
	{
		if (bson_iter_init(&iter, bson) && bson_iter_find_descendant(&iter, "_id", &id)
			&& BSON_ITER_HOLDS_OID(&id))
		{
			temp = (bson_oid_t *)bson_iter_oid(&id);
			bson_oid_copy(temp, &mongo.oid);
			bson_destroy(query);
			mongoc_cursor_destroy(cursor);
			return (0);
		}
	}
	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	return (1);
}

/*Atualiza o banco de dados com novas informações*/
static void	db_update(char *s)
{
	bson_t			*query;
	bson_t			update;
	bson_t			*user_data;
	bson_error_t	error;

	query = NULL;
	query = BCON_NEW("_id", BCON_OID(&mongo.oid));
	bson_init(&update);
	user_data = bson_new_from_json((const uint8_t *)s, -1, &error);
	bson_append_document(&update, "$set", 4, user_data);
	if (!mongoc_collection_update_one(mongo.collection, query, &update, NULL, NULL, &error))
		fprintf(stderr, "%s\n", mongo.error.message);
	bson_destroy(query);
	bson_destroy(&update);
	bson_destroy(user_data);
}

int	mongo_handler(char *s)
{
	char	*mongo_client = getenv("MONGO_CLIENT");
	
	mongo.client = mongoc_client_new(mongo_client);
	mongo.collection = mongoc_client_get_collection (mongo.client, "users", "info");
	bson_oid_init(&mongo.oid, NULL);
	if(db_query())
	{
		mongo.insert = bson_new_from_json((const uint8_t *)s, strlen(s), &mongo.error);
		if (!mongoc_collection_insert_one(mongo.collection, mongo.insert, NULL, NULL, &mongo.error))
			fprintf(stderr, "%s\n", mongo.error.message);
		bson_destroy(mongo.insert);
	}
	else
		db_update(s);
	mongoc_collection_destroy(mongo.collection);
	mongoc_client_destroy(mongo.client);
	mongoc_cleanup();
	return (1);
}