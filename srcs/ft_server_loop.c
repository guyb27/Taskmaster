/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   server.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2042/02/19 22:41:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 03:09:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

static int	ft_new_client(t_server *server, int *max_fd, t_tm *tm)
{
	char	*tmp;

	tmp = NULL;
	server->csock = accept(server->sock, (t_sockaddr*)&server->csin,
			&(socklen_t){ sizeof(server->csin) });
	if (server->csock == SOCKET_ERROR)
	{
		ft_perror("accept()");
		return (1);
	}
	tmp = ft_get_logo();
	if (send(server->csock, tmp, ft_strlen(tmp) + 1, 0) < 0)
		ft_server_quit(server, "send() prompt");
	ft_strdel(&tmp);
	ft_sprintf(&tmp, ft_cmd_help(tm));
	if (send(server->csock, tmp, ft_strlen(tmp) + 1, 0) < 0)
		ft_server_quit(server, "send() prompt");
	ft_strdel(&tmp);
	if (send(server->csock, PROMPT, ft_strlen(PROMPT) + 1, 0) < 0)
		ft_server_quit(server, "send() prompt");
	*max_fd = server->csock > *max_fd ? server->csock : *max_fd;
	FD_SET(server->csock, &server->rdfs);
	server->clients[server->clients_cnt] = server->csock;
	server->clients_cnt++;
	return (0);
}

static void	ft_receive_request(t_server *server, t_tm *tm)
{
	int		i;

	i = -1;
	while (++i < server->clients_cnt)
	{
		if (FD_ISSET(server->clients[i], &server->rdfs))
		{
			if (recv(server->clients[i], tm->cmd, BUF_SIZE - 1, 0) <= 0)
				ft_remove_client(server, i);
			else if (ft_cmd_check(tm->cmd))
			{
				ft_process_cmd(tm);
				if (send(server->clients[i], tm->ret, ft_strlen(tm->ret) + 1, 0)
																			< 0)
				{
					ft_strdel(&tm->ret);
					ft_server_quit(server, "send()");
				}
			}
			if (send(server->clients[i], PROMPT, ft_strlen(PROMPT) + 1, 0) <= 0)
				ft_remove_client(server, i);
			break ;
		}
	}
}

void		ft_init_server_loop(t_server *server, t_tm *tm)
{
	ft_bzero(tm->cmd, sizeof(tm->cmd));
	FD_ZERO(&server->rdfs);
	FD_SET(STDIN_FILENO, &server->rdfs);
	FD_SET(server->sock, &server->rdfs);
}

int			ft_server_loop(t_server *server, t_tm *tm)
{
	int		max_fd;
	int		i;

	max_fd = server->sock;
	while ((i = -1))
	{
		ft_init_server_loop(server, tm);
		while (++i < server->clients_cnt)
			FD_SET(server->clients[i], &server->rdfs);
		if (select(max_fd + 1, &server->rdfs, NULL, NULL, NULL) == -1)
			ft_server_quit(server, "select()");
		if (FD_ISSET(STDIN_FILENO, &server->rdfs))
			break ;
		else if (FD_ISSET(server->sock, &server->rdfs))
		{
			if (ft_new_client(server, &max_fd, tm))
				continue;
		}
		else
			ft_receive_request(server, tm);
	}
	ft_server_quit(server, NULL);
	return (0);
}
