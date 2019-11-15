/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 09:26:05 by gmadec      ###    #+. /#+    ###.fr     */
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
	SOCKADDR_IN sin;
	struct hostent *hostinfo;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		perror("socket()");
		return (-1);
	}
	ft_bzero(&sin, sizeof(SOCKADDR_IN));
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		fprintf (stderr, "Unknown host %s.\n", address);
		return (-1);
	}
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
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
	/*while (j < 100)
	{
		ft_bzero(g_tab.cmd[j].cmd, sizeof(g_tab.cmd[j].cmd));
		ft_bzero(g_tab.process[j], sizeof(g_tab.process[j]));
		j++;
	}
	j = 0;
	*/
	ft_bzero(g_command, sizeof(g_command));
	ft_bzero(g_process, sizeof(g_process));
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
	printf("--------PARSE----------\n");
	i = 0;
	while (g_tab.cmd[i].cmd[0])
	{
		printf("CMD [%d]: [%s], [%s]\n", i, g_tab.cmd[i].cmd, !g_tab.cmd[i].arg ? "Pas d'argument" : g_tab.cmd[i].arg == 1 ? "Arg" : "Arg + All");
		i++;
	}
	i = 0;
	while (g_tab.process[i] && g_tab.process[i][0])
	{
		printf("PROCESS [%d]: [%s]\n", i, g_tab.process[i]);
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

static int		shell(const char *addr, int port)
{
	int sock;
	char buffer[BUF_SIZE];
	fd_set rdfs;
	int		n;

	if ((sock = init_connection(addr, port)) == -1 || get_start_requests(sock))
		return (1);
	get_term_raw_mode(1);
	while(1)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(sock, &rdfs);
		if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}
		if(FD_ISSET(STDIN_FILENO, &rdfs))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			ft_get_user_input();
			if (g_cmd && !ft_strncmp(FT_KEY_CTRL_D, g_cmd, 4))
			{
				ft_strdel(&g_cmd);
				closesocket(sock);
				get_term_raw_mode(0);
				return (0);
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
		}
		else if(FD_ISSET(sock, &rdfs))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			if (read_server(sock, buffer) == 0)
			{
				get_term_raw_mode(0);
				printf("Server disconnected !\n");
				break;
			}
			if (ft_strcmp(buffer, g_cl_prompt))
			{
				ft_putstr(buffer);
				ft_putstr(g_cl_prompt);
			}
			get_term_raw_mode(1);
		}
	}
	closesocket(sock);
	return (0);
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
