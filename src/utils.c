/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogerio <rogerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:44:09 by rogerio           #+#    #+#             */
/*   Updated: 2021/08/22 13:21:06 by rogerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../api.h"

extern t_api	source;

void	serve_file(struct mg_http_message *request, struct mg_connection *c, char *path)
{
	struct mg_http_serve_opts    opts = {.mime_types = "text=text/html", .extra_headers = "AA: bb\r\nCC: dd\r\n"};
	mg_http_serve_file(c, request, path, &opts);
}

void http_reply_and_free(struct mg_connection *conn, int status, char *header, char *body)
{
	mg_http_reply(conn, status, header, body);
	free(body);
}

double json_loop(char *needle)
{
	char *haystack;
	double sum;
	double times;
	int len = strlen(needle);

	haystack = strstr(source.content, needle);
	sum = 0;
	times = 0;
	while (haystack)
	{
		sum += atoi(haystack + len);
		haystack = haystack + len;
		haystack = strstr(haystack, needle);
		times++;
	}
	if (times == 0)
		return (0);
	return (sum / times);
}

void info_format(char **info)
{
	int		name_len;
	int		eval_points;
	int		total_len;
	double	global_avg;
	double	retry_avg;
	char	*name;
	char	*trail;
	char	*trooper;
	char	*eval_comm;

	mjson_find(source.content, source.content_len, "$.displayname", (const char **)&name, &name_len);
	global_avg	=	json_loop("\"final_mark\":");
	retry_avg	=	json_loop("\"occurrence\":");
	trail		=	get_trail();
	trooper		=	get_trooper();
	eval_points	=	get_eval_points();
	eval_comm	=	get_eval_comment(eval_points);
	total_len =		strlen(source.user) + name_len + strlen(trail) + strlen(eval_comm) + strlen(trooper) + 170;

	free(source.content);
	*info = (char *)calloc(total_len, sizeof(char));
	
	mjson_snprintf(*info, total_len, "{%Q: %Q, %Q: %.*s, %Q: %Q, %Q: %d, %Q: %Q, %Q: %.*g, %Q: %.*g, %Q: %Q}",
		"login", source.user,
		"full_name", name_len, name,
		"trail", trail,
		"evaluation_points", eval_points,
		"eval_points_comment", eval_comm,
		"global_average", 2, global_avg,
		"retrys_average", 2, retry_avg,
		"stormtrooper?", trooper
	);
	free(trail);
	free(trooper);
	free(eval_comm);
}
