/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 03:34:26 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/24 10:18:09 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

extern t_api	source;


int get_user(struct mg_http_message request)
{
	sprintf(source.user, "%.*s", (int)request.uri.len - 8, request.uri.ptr + 8);
	if (!strcmp("", source.user))
	{
		source.status = 404;
		return (0);
	}
	return (1);
}

void get_token(void)
{
	source.conn_bool = 0;
	mg_http_connect(&source.mgr, INTRA_ADDRESS, token_callback, &source.conn_bool);
	while (true && !source.conn_bool)
		mg_mgr_poll(&source.mgr, 1000);
}

void	get_status(struct mg_http_message response)
{
	source.status = atoi(strstr(response.message.ptr, "Status") + 8);
}

void get_intra_info(void)
{
	source.conn_bool = 0;
	mg_http_connect(&source.mgr, INTRA_ADDRESS, info_callback, &source.conn_bool);
	while (true && !source.conn_bool)
		mg_mgr_poll(&source.mgr, 1000);
}

void	get_content(struct mg_http_message *response)
{
	source.content = (char *)calloc(response->body.len + 1, sizeof(char));
	source.content_len = response->body.len;
	sprintf(source.content,"%.*s", (int)response->body.len, response->body.ptr);
}

char	*get_trail(void)
{
	char *trail;
	
	trail =	strstr(source.content, "\"Libft\"");
	if (trail)
	{
		trail = strstr(source.content, "\"ft_transcendence\"");
		if (trail)
			return(strdup("Specialization"));
		else
			return(strdup("Knowledge"));
	}
	else
		return(strdup("Basecamp"));
}

char	*get_trooper(void)
{
	char *trooper;
	
	trooper =	strstr(source.content, "\"https://cdn.intra.42.fr/users/default.png\"");
	if (trooper)
		return (strdup("Yes"));
	else
		return (strdup("No"));
}

char	*get_eval_comment(int corr)
{
	if (corr < 0)
		return (strdup("???? start evaluating now!"));
	else if (corr < 10)
		return (strdup("Fair enough"));
	else
		return (strdup("Why some have so much while others have so little"));
}

int	get_eval_points(void)
{
	return (atoi(strstr(source.content, "\"correction_point\":") + 19));
}
