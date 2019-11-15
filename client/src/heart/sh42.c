/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 11:10:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int read_server(int sock, char *buffer)
{
	int n = 0;

	if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
	{
		perror("recv()");
		exit(errno);
	}
	buffer[n] = 0;
	return n;
}


static void write_server(int sock, const char *buffer)
{
	if(send(sock, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}


static int init_connection(const char *address, int port)
{
	int sock;
	struct sockaddr_in sin;
	struct hostent *hostinfo;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket()");
		return (-1);
	}
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		fprintf (stderr, "Unknown host %s.\n", address);
		return (-1);
	}
	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if(connect(sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1)
	{
		perror("connect()");
		return (-1);
	}
	return sock;
}

void			ft_get_tab_elem(char *str)
{
	char		**tablo;
	char		**tab_tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	int			state;

	state = 0;
	tablo = ft_strsplit(str, '\n');
	while (j < 100)
	{
		ft_bzero(g_tab.cmd[j].cmd, sizeof(g_tab.cmd[j].cmd));
		ft_bzero(g_tab.process[j], sizeof(g_tab.process[j]));
		j++;
	}
	j = 0;
	ft_bzero(g_tab.cmd, sizeof(g_tab.cmd));
	ft_bzero(g_tab.process, sizeof(g_tab.process));
	//ft_bzero(g_tab, sizeof(g_tab));
	while (tablo[i])
	{
		tab_tmp = ft_strsplit(tablo[i], ' ');
		if (tab_tmp && tab_tmp[0] && tab_tmp[0][0] == '\t')//CMD || PROCESS
		{
			if (state == 2)//COMMANDE
			{
				ft_strcpy(g_tab.cmd[j].cmd, tab_tmp[0] + 1);//COMMANDE
				if (tab_tmp[1])//PROCESS
				{
					g_tab.cmd[j].arg = 1;
					if (tab_tmp[2] && tab_tmp[3])//ALL
						g_tab.cmd[j].arg = 2;
				}
				j++;
			}
			else//PROCESS
				ft_strcpy(g_tab.process[k++], tab_tmp[0] + 1);
		}
		else//TITLE
			state++;
		i++;
	}
}

static int		get_start_requests(int sock)
{
	int		i;
	char buffer[BUF_SIZE];
	int n;
	int j;
	int debut;

	i = 0;
	while (i < 3 && ft_memset(buffer, 0, sizeof(buffer)))
	{
		if (!(n = read_server(sock, buffer)))
		{
			printf("Server disconnected !\n");
			return (1);
		}
		j = 0;
		debut = 0;
		while (j < n)
		{
			if (buffer[j] == '\0')
			{
				ft_putstr(buffer + debut);
				if (i == 1)
					ft_get_tab_elem(buffer + debut);
				else if (i == 2)
					g_cl_prompt = ft_strdup(buffer + debut);
				debut = j + 1;
				i++;
			}
			j++;
		}
	}
	return (0);
}

int				ft_thread_read_input(int sock)
{
		ft_get_user_input();
		if (g_cmd && !ft_strncmp(FT_KEY_CTRL_D, g_cmd, 4))
		{
			ft_strdel(&g_cmd);
			close(sock);
			get_term_raw_mode(0);
			return (-1);
		}
		else if (g_cmd && !ft_str_isblank(g_cmd))
		{
			history_save((char ***)NULL, g_cmd, 1, (char *)NULL);
			write_server(sock, g_cmd);
		}
		else
		{
			if (g_cmd && g_cmd[0] && g_cmd[1])
				ft_putstr(g_cl_prompt);
			get_term_raw_mode(1);
		}
		ft_strdel(&g_cmd);
	return (0);
}

int				ft_thread_read_server(int sock, fd_set *rdfs)
{
	char buffer[BUF_SIZE];

	if(FD_ISSET(STDIN_FILENO, rdfs))
	{
	}
	else if(FD_ISSET(sock, rdfs))
	{
		ft_memset(buffer, 0, sizeof(buffer));
		if (read_server(sock, buffer) == 0)
		{
			get_term_raw_mode(0);
			printf("Server disconnected !\n");
			return (1);
		}
		if (ft_strcmp(buffer, g_cl_prompt))
		{
			ft_putstr(buffer);
			ft_putstr(g_cl_prompt);
		}
		get_term_raw_mode(1);
	}
	return (0);
}

static int		shell(const char *addr, int port)
{
	int sock;
	fd_set rdfs;
	int		loop;

	loop = 0;
	if ((sock = init_connection(addr, port)) == -1 || get_start_requests(sock))
		return (1);
	get_term_raw_mode(1);
	while(!loop)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(sock, &rdfs);
		if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
			return (close + ft_putstr("Select error\n"));
		if(FD_ISSET(STDIN_FILENO, &rdfs))
			loop = ft_thread_read_input(sock);
		else if(FD_ISSET(sock, &rdfs))
			loop = ft_thread_read_server(sock, &rdfs);
	}
	close(sock);
	return (loop == 1 || loop == 0 ? 0 : 1);
}

int				main(int ac, const char **av)
{
	int		ret;

	if (ac < 2 || !ft_atoi(av[2])) {
		fprintf(stderr, "Usage: %s <host> <port>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (init_shell(ac, av))
	{
		ft_putstr("Taskmaster can't run in non-interactive mode.");
		return (EXIT_FAILURE);
	}
	ret = shell(av[1], ft_atoi(av[2]));
	exit_shell();
	return (ret);
}
