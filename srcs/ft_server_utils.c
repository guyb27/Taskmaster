/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void				ft_server_error(t_tm *tm, char *error)
{
	int				err;

	err = errno;
	ft_printf("\nServer quit !!!\n");
	if (errno && error)
		ft_perror(error);
	ft_quit(tm);
}

void				ft_remove_client(t_server *server, int client_id)
{
	ft_printf("A client left\n");
	close(server->clients[client_id]);
	ft_memmove(&server->clients[client_id], &server->clients[client_id + 1],
			(server->clients_cnt - client_id - 1) * sizeof(t_socket));
	server->clients_cnt--;
}

int					ft_cmd_check(char *cmd)
{
	unsigned long	i;

	while (ft_strlen(cmd) && ft_strchr("\n\r", cmd[ft_strlen(cmd) - 1]))
		cmd[ft_strlen(cmd) - 1] = '\0';
	i = 0;
	while (isprint(cmd[i]))
		i++;
	return (i > 0 && strlen(cmd) == i);
}
