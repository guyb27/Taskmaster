/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_server_utils.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 06:26:10 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/24 00:07:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void				ft_server_quit(t_server *server, char *error)
{
	int				err;
	int				i;

	err = errno;
	ft_printf("\nServer quit !!!\n");
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

t_server			ft_init_server(char *ip, int port)
{
	t_server		server;

	ft_bzero(&server, sizeof(t_server));
	server.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server.sock == INVALID_SOCKET)
		ft_server_quit(&server, "socket()");
	server.sin.sin_addr.s_addr = inet_addr(ip);
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

void				ft_remove_client(t_server *server, int client_id)
{
	ft_printf("A client left\n");
	//	close(server->clients[client_id]);
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
