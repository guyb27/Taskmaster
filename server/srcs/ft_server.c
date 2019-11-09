/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   server.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2042/02/19 22:41:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 03:52:16 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void		ft_server_quit(t_server *server, char *error)
{
	int err;
	int	i;

	err = errno;
	if (errno && error)
		ft_perror(error);
	i = -1;
	while (++i < server->clients_cnt)
		close(server->clients[i]);
	close(server->sock);
	close(server->csock);
	// faudra pas oublier à rajouter le munmap()
	exit(err);
}

t_server	ft_init_server(int port)
{
	t_server		server;

	ft_bzero(&server, sizeof(t_server));
	server.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server.sock == INVALID_SOCKET)
		ft_server_quit(&server, "socket()");
	server.sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin.sin_port = htons(port);
	server.sin.sin_family = AF_INET;
	if (setsockopt(server.sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 },
															sizeof(int)) < 0)
		ft_server_quit(&server, "setsockopt()");
	if (bind(server.sock, (t_sockaddr*)&server.sin, sizeof(server.sin)) == -1)
		ft_server_quit(&server, "bind()");
	if (listen(server.sock, MAX_CLIENTS) == SOCKET_ERROR)
		ft_server_quit(&server, "listen()");
	return (server);
}

static void	ft_remove_client(t_server *server, int client_id)
{
	printf("A client left\n");
//	close(server->clients[client_id]);
	ft_memmove(&server->clients[client_id], &server->clients[client_id + 1],
			(server->clients_cnt - client_id - 1) * sizeof(t_socket));
	server->clients_cnt--;
}

int			ft_cmd_check(char *cmd)
{
	unsigned long	i;

	while (ft_strlen(cmd) && ft_strchr("\n\r", cmd[ft_strlen(cmd) - 1]))
		cmd[ft_strlen(cmd) - 1] = '\0';
	i = 0;
	while (isprint(cmd[i]))
		i++;
	return (i > 0 && strlen(cmd) == i);
}

int			ft_server_loop(t_server *server, t_tm *tm)
{
	int		max_fd;
	int		i;

	max_fd = server->sock;
	while (1)
	{
		ft_bzero(tm->cmd, sizeof(tm->cmd));
		FD_ZERO(&server->rdfs);

		// add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &server->rdfs);

		// add the connection socket
		FD_SET(server->sock, &server->rdfs);

		// add socket of each client
		i = -1;
		while (++i < server->clients_cnt)
			FD_SET(server->clients[i], &server->rdfs);

		if (select(max_fd + 1, &server->rdfs, NULL, NULL, NULL) == -1)
			ft_server_quit(server, "select()");

		// something from standard input : i.e keyboard
		if (FD_ISSET(STDIN_FILENO, &server->rdfs))
		{
			// stop process when type on keyboard
			break;
		}
		else if (FD_ISSET(server->sock, &server->rdfs))
		{
			// new client
			server->csock = accept(server->sock, (t_sockaddr*)&server->csin,
										&(socklen_t){ sizeof(server->csin) });
			if (server->csock == SOCKET_ERROR)
			{
				ft_perror("accept()");
				continue;
			}
			if (send(server->csock, PROMPT, ft_strlen(PROMPT), 0) < 0)
				ft_server_quit(server, "send() prompt");
			// what is the new maximum fd ?
			max_fd = server->csock > max_fd ? server->csock : max_fd;
			FD_SET(server->csock, &server->rdfs);
			server->clients[server->clients_cnt] = server->csock;
			server->clients_cnt++;
		}
		else
		{
			i = -1;
			while (++i < server->clients_cnt)
			{
				// a client is talking
				if (FD_ISSET(server->clients[i], &server->rdfs))
				{
					
					if (recv(server->clients[i], tm->cmd, BUF_SIZE - 1, 0) <= 0)
						ft_remove_client(server, i);
					else if (ft_cmd_check(tm->cmd))
					{
						ft_process_cmd(tm);
						if (send(server->clients[i], tm->ret, ft_strlen(tm->ret), 0) < 0)
						{
							ft_strdel(&tm->ret);
							ft_server_quit(server, "send()");
						}
					}
					if (send(server->clients[i], PROMPT, ft_strlen(PROMPT), 0) <= 0)
						ft_remove_client(server, i);
						//ft_server_quit(server, "send() prompt 2");
					break;
				}
			}
		}
	}
	ft_server_quit(server, NULL);
	return (0);
}
