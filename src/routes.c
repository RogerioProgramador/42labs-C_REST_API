/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:20:58 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 17:24:29 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

void get_route(struct mg_http_message *request, struct mg_connection *c)
{
	if(mg_http_match_uri(request, "/api/v1/*"))
		info_request(request, c);
	else if(mg_http_match_uri(request, "/"))
		serve_file(request, c, "./etcs/index.html");
	else if(mg_http_match_uri(request, "/docs"))
		serve_file(request, c, "./etcs/docs.html");
	else
		mg_http_reply(c, 405, "", "{\"ERRO\": %s}\n", "Rota invalida");
}

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void put_route(struct mg_http_message *request, struct mg_connection *c)
{
	if(mg_http_match_uri(request, "/api/v1/put"))
		mg_http_reply(c, 200, "", "{\"OK\": %s}\n", "Implementação de PUT não concluída");
	else
		mg_http_reply(c, 400, "", "{\"ERRO\": %s}\n", "Rota invalida");
}

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void post_route(struct mg_http_message *request, struct mg_connection *c)
{
	if(mg_http_match_uri(request, "/api/v1/post"))
		mg_http_reply(c, 200, "", "{\"OK\": %s}\n", "Implementação de POST não concluída");
	else
		mg_http_reply(c, 400, "", "{\"ERRO\": %s}\n", "Rota invalida");
}

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void delete_route(struct mg_http_message *request, struct mg_connection *c)
{
	if(mg_http_match_uri(request, "/api/v1/delete"))
		mg_http_reply(c, 200, "", "{\"OK\": %s}\n", "Implementação de DELETE não concluída");
	else
		mg_http_reply(c, 400, "", "{\"ERRO\": %s}\n", "Rota invalida");
}

/* ATENÇÃO: ROTA NÃO IMPLEMENTADA */
void patch_route(struct mg_http_message *request, struct mg_connection *c)
{
	if(mg_http_match_uri(request, "/api/v1/patch"))
		mg_http_reply(c, 200, "", "{\"OK\": %s}\n", "Implementação de PATCH não concluída");
	else
		mg_http_reply(c, 400, "", "{\"ERRO\": %s}\n", "Rota invalida");
}
