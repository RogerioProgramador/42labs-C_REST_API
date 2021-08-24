/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 00:22:20 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 10:54:59 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

extern t_api source;

void token_callback(struct mg_connection *conn, int ev, void *ev_data, void *fn)
{
	struct mg_http_message *response = (struct mg_http_message *)ev_data;
	struct mg_str host = mg_url_host(INTRA_ADDRESS);
	char *client_id = getenv("C_ID");
	char *client_secret = getenv("C_SEC");

	if (ev == MG_EV_CONNECT)
	{
		if (mg_url_is_ssl(INTRA_ADDRESS))
		{
			struct mg_tls_opts opts = {.srvname = host};
			mg_tls_init(conn, &opts);
		}
		mg_printf(	conn,
					"POST /oauth/token HTTP/1.0\r\n"
					"Host: api.intra.42.fr\r\n"
					"Accept: */*\r\n"
					"Content-Length: 183\r\n"
					"\r\n"
					"grant_type=client_credentials&client_id=%s&client_secret=%s",
					client_id, client_secret);
	}
	else if (ev == MG_EV_HTTP_MSG)
	{
		get_status(*response);
		if (source.status == SUCCESS)
		{
			source.token[65] = 0;
			sprintf(source.token, "%.*s", 64, response->body.ptr + 17);
		}
		conn->is_closing = 1;
		source.conn_bool = 1;
	}
	else if (ev == MG_EV_ERROR)
		conn->is_closing = 1;
	(void)fn;
}

void	info_callback(struct mg_connection *conn, int ev, void *ev_data, void *fn)
{
	struct mg_http_message *response = (struct mg_http_message *)ev_data;
	struct mg_str host = mg_url_host(INTRA_ADDRESS);
	
	if (ev == MG_EV_CONNECT)
	{
		if (mg_url_is_ssl(INTRA_ADDRESS))
		{
			struct mg_tls_opts opts = {.srvname = host};
			mg_tls_init(conn, &opts);
		}
		mg_printf(	conn,
					"GET /v2/users/%s HTTP/1.0\r\n"
					"Host: api.intra.42.fr\r\n"
					"Accept: */*\r\n"
					"Authorization: Bearer %s\n"
					"\r\n",
					source.user, source.token);
	}
	else if (ev == MG_EV_HTTP_MSG)
	{
		get_status(*response);
		if (source.status == SUCCESS)
			get_content(response);
		conn->is_closing = 1;
		source.conn_bool = 1;
	}
	else if (ev == MG_EV_ERROR)
		conn->is_closing = 1;
	(void)fn;
}
