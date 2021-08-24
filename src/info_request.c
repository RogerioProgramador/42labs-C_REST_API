/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:28:22 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 15:40:54 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

extern t_api	source;

void info_request(struct mg_http_message *request, struct mg_connection *conn)
{
	if(get_user(*request))
	{
		get_token();
		get_intra_info();
	}
	if (source.status == SUCCESS)
	{
		info_format(&source.content);
		if(!mongo_handler(source.content))
			mg_http_reply(conn, 500, "", "{\"ERRO:\" 500}\n");
		else
			http_reply_and_free(conn, 200, "content-type application/json; charset=utf-8 \r\n", source.content);
	}
	else
		mg_http_reply(conn, source.status, "", "{\"ERRO:\" %i}\n", source.status);
}
