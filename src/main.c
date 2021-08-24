/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:53:39 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 15:40:25 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

t_api source;

static int	get_method(const char *method)
{
	if (!strncmp(method, "GET", 3))
		return (GET);
	else if (!strncmp(method, "POST", 4))
		return (POST);
	else if (!strncmp(method, "PUT", 3))
		return (PUT);
	else if (!strncmp(method, "DELETE", 6))
		return (DELETE);
	else if (!strncmp(method, "PATCH", 5))
		return (PATCH);
	else
		return (METHODS);
}

static void	callback(struct mg_connection *conn, int ev, void *ev_data, void *fn)
{
	struct mg_http_message		*request;

	request = (struct mg_http_message *)ev_data;
	if (ev == MG_EV_HTTP_MSG)
	{
		int	method = get_method(request->method.ptr);
		if (method == GET)
			get_route(request, conn);
		else if (method == POST)
			post_route(request, conn);
		else if (method == PUT)
			put_route(request, conn);
		else if (method == DELETE)
			delete_route(request, conn);
		else if (method == PATCH)
			patch_route(request, conn);
		else
			mg_http_reply(conn, 400, "", "Bad Request", method);	
	}
	(void)fn;
}

int	main(void)
{
	mg_mgr_init(&source.mgr);
	mongoc_init();
	mg_http_listen(&source.mgr, ADDRESS, callback, NULL);
	while (true)
		mg_mgr_poll(&source.mgr, 1000);
	mg_mgr_free(&source.mgr);
}
