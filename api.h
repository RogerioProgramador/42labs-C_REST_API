/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:25:41 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 15:51:48 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_H
# define API_H

# define SUCCESS 200
# define ADDRESS "http://0.0.0.0:4242"
# define INTRA_ADDRESS "https://api.intra.42.fr/oauth/token"

# include "mongoose/mongoose.h"
# include "mjson/mjson.h"
# include <string.h>
# include <mongoc/mongoc.h>
# include <time.h>

typedef struct		s_api
{
	struct	mg_mgr mgr;
	int		conn_bool;

	char	user[9];
	char	token[65];

	int		status;
	char	*content;
	int		content_len;
}					t_api;

typedef struct	s_mongo
{
	mongoc_client_t		*client;
	mongoc_collection_t	*collection;
	bson_t				*insert;
	bson_error_t		error;
	bson_oid_t			oid;
}				t_mongo;

enum e_methods
{
	GET,
	POST,
	PUT,
	DELETE,
	PATCH,
	METHODS
};

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void	put_route(struct mg_http_message *request, struct mg_connection *c);

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void	post_route(struct mg_http_message *request, struct mg_connection *c);

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void	delete_route(struct mg_http_message *request, struct mg_connection *c);

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void	patch_route(struct mg_http_message *request, struct mg_connection *c);

/* Verifica se a rota é valida e, caso seja, da seguimento ao request */
void	get_route(struct mg_http_message *request, struct mg_connection *c);

/* Responsável por gerenciar a rota que retorna as informações do usuário e as armazena no banco de dados */
void	info_request(struct mg_http_message *request, struct mg_connection *conn);

/* entrega para o ponteiro do parametro uma string com informações específicas formatadas para json*/
void	info_format(char **info);

/*Callbacks*/

void	token_callback(struct mg_connection *conn, int ev, void *ev_data, void *fn);

void	info_callback(struct mg_connection *conn, int ev, void *ev_data, void *fn);

/*Getters*/

/*Coloca o usuário em source->user*/
int		get_user(struct mg_http_message request);

/* Busca o token na api da 42 e o coloca em source->token */
void	get_token(void);

/* Busca a informação na api da 42 */
void	get_intra_info(void);

/* Faz a alocação e coloca o conteudo do body em source.content */
void	get_content(struct mg_http_message *response);

/*Retorna a trilha de conhecimento*/
char	*get_trail(void);

/* Retorna uma string com Yes caso a foto da intra seja de um stormtrooper senão envia um No */
char	*get_trooper(void);

/* Retorna um comentário a respeito do seu número de evaluation points */
char	*get_eval_comment(int corr);

/* Busca o Status em response e o colocar em sorce.status */
void	get_status(struct mg_http_message response);

/* Retorna o número de evaluation points */
int		get_eval_points(void);

/* itera pelo json procurando a string e somando os valores, retornando uma média */
double	json_loop(char *needle);

/* o reply e libera o conteúdo alocado em body */
void	http_reply_and_free(struct mg_connection *conn, int status, char *header, char *body);

/* Lida com a adição ou atualização do banco de dados */
int		mongo_handler(char *s);

/* Disponibiliza o arquivo que esta em path na página desejada */
void	serve_file(struct mg_http_message *request, struct mg_connection *c, char *path);

#endif