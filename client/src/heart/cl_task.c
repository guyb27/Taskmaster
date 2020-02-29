/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:00 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 07:05:26 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

static int				init_connection(const char *address, int port)
{
	int					sock;
	struct sockaddr_in	sin;
	struct hostent		*hostinfo;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket()");
		return (-1);
	}
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		ft_putstr("Unknown host.\n");
		return (-1);
	}
	sin.sin_addr = *(struct in_addr *)hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1)
	{
		ft_putstr("connect()");
		return (-1);
	}
	return (sock);
}

static int				ft_thread_read_input(int sock, int *reload_bool)
{
	ft_get_user_input();
	if (g_cl.cmd && !ft_strncmp((char[4]){4, 0, 0, 0}, g_cl.cmd, 4))
	{
		close(sock);
		get_term_raw_mode(0);
		return (-1 + ft_strdel(&g_cl.cmd));
	}
	else if (g_cl.cmd && !ft_str_isblank(g_cl.cmd))
	{
		history_save((char ***)NULL, g_cl.cmd, 1, (char *)NULL);
		*reload_bool = !ft_strcmp("reload\n", g_cl.cmd) ? 1 : *reload_bool;
		if (write_server(sock, g_cl.cmd) == -1)
			return (1 + ft_strdel(&g_cl.cmd));
	}
	else
	{
		if (g_cl.cmd && g_cl.cmd[0] && g_cl.cmd[1])
			ft_putstr(g_cl.prompt);
		get_term_raw_mode(1);
	}
	return (ft_strdel(&g_cl.cmd));
}

static int				ft_thread_read_server(int sock, int *reload_bool)
{
	char				buffer[BUF_SIZE];
	int					n;

	ft_memset(buffer, 0, sizeof(buffer));
	get_term_raw_mode(0);
	if ((n = read_server(sock, buffer)) <= 0)
	{
		get_term_raw_mode(0);
		ft_putstr(!n ? "\nServer disconnected !\n" : "");
		return (1);
	}
	if (ft_strcmp(buffer, g_cl.prompt))
	{
		ft_putstr(buffer);
		if (*reload_bool)
		{
			*reload_bool = 0;
			ft_get_tab_elems(buffer);
		}
		ft_putstr(g_cl.prompt);
	}
	get_term_raw_mode(1);
	return (0);
}

static int				shell(int sock)
{
	fd_set				rdfs;
	int					loop;
	int					reload_bool;

	loop = 0;
	reload_bool = 0;
	if (ft_init_parse(sock))
		return (1);
	get_term_raw_mode(1);
	while (!loop)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(sock, &rdfs);
		if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
			return (close(sock) + ft_putstr("Select error\n"));
		if (FD_ISSET(STDIN_FILENO, &rdfs))
			loop = ft_thread_read_input(sock, &reload_bool);
		else if (FD_ISSET(sock, &rdfs))
			loop = ft_thread_read_server(sock, &reload_bool);
	}
	close(sock);
	return (loop == 1 || loop == 0 ? 0 : 1);
}

int						main(int ac, const char **av)
{
	int					ret;
	int					sock;
	int					port;

	if (ac < 2 || (port = ft_atoi(av[2])) <= 0)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (init_shell(av))
	{
		ft_putstr("Taskmaster can't run in non-interactive mode.");
		return (EXIT_FAILURE);
	}
	if (!((sock = init_connection(av[1], port)) == -1))
		ret = shell(sock) ? 1 : 0;
	else
		ret = 1;
	exit_shell();
	return (ret);
}
