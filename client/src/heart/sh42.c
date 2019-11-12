/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 06:39:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"
//#include "heart.h"

static void		ft_print_logo_and_init(void)
{
	g_cmd = NULL;
	ft_putstr(CYANB);
	printf(" _            _                        _ \n");
	printf("| |          | |                      | |           \n");
	printf("| |_ __ _ ___| | ___ __ ___   __ _ ___| |_ ___ _ __ \n");
	printf("| __/ _` / __| |/ / '_ ` _ \\ / _` / __| __/ _ \\ '__|\n");
	printf("| || (_| \\__ \\   <| | | | | | (_| \\__ \\ ||  __/ |   \n");
	printf(" \\__\\__,_|___/_|\\_\\_| |_| |_|\\__,_|___/\\__\\___|_|\n");
	printf("                                                 \n\n");
	ft_putstr(STOP);
}


static void end_connection(int sock)
{
	closesocket(sock);
}

static int read_server(SOCKET sock, char *buffer)
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


static void write_server(SOCKET sock, const char *buffer)
{
	if(send(sock, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}


static int init_connection(const char *address, int port)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };
	struct hostent *hostinfo;

	if(sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		fprintf (stderr, "Unknown host %s.\n", address);
		exit(EXIT_FAILURE);
	}

	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		perror("connect()");
		exit(errno);
	}

	return sock;
}

static int		shell(const char *addr, int port)
{
	int sock = init_connection(addr, port);
	char buffer[BUF_SIZE];
	fd_set rdfs;
	int		i = 0;
	int		j = 0;
	//ft_print_logo_and_init();

	while (i < 3)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(sock, &rdfs);
		if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}
		else if(FD_ISSET(sock, &rdfs))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			int n = read_server(sock, buffer);
			if(n == 0)
			{
				printf("Server disconnected !\n");
				return (0);
			}
			j = 0;
				printf("0I: [%d]\n", i);
			while (j < n)
			{
				printf("%c", buffer[j]);
				if (buffer[j] == '\0')
					i++;
				j++;
			}
				printf("1I: [%d]\n", i);
		}
	}
	ft_memset(buffer, 0, sizeof(buffer));
	if (read_server(sock, buffer) == 0)
	{
		printf("Server disconnected !\n");
		get_term_raw_mode(0);
		return (0);
	}
	printf("%s", buffer);
	ft_memset(buffer, 0, sizeof(buffer));
	if (read_server(sock, buffer) == 0)
	{
		printf("Server disconnected !\n");
		get_term_raw_mode(0);
		return (0);
	}
	printf("%s", buffer);
	ft_memset(buffer, 0, sizeof(buffer));
	if (read_server(sock, buffer) == 0)
	{
		printf("Server disconnected !\n");
		get_term_raw_mode(0);
		return (0);
	}
	g_cl_prompt = ft_strdup(buffer);
		ft_putstr(g_cl_prompt);
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
			//	printf("00\n");
				ft_strdel(&g_cmd);
				end_connection(sock);
				get_term_raw_mode(0);
				return (0);
			}
			else if (g_cmd && !ft_str_isblank(g_cmd))
			{
			//	printf("11\n");
				history_save((char ***)NULL, g_cmd, 1, (char *)NULL);
				write_server(sock, g_cmd);
				if (!ft_strcmp("exit\n", g_cmd))
				{
					end_connection(sock);
					get_term_raw_mode(0);
					ft_strdel(&g_cmd);
					return (0);
				}
			}
			else
			{
				//printf("22G_CMD: [%s]\n", g_cmd);
				if (g_cmd && g_cmd[0] && g_cmd[1])
					ft_putstr(g_cl_prompt);
				get_term_raw_mode(1);
			}
			ft_strdel(&g_cmd);
		}
		else if(FD_ISSET(sock, &rdfs))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			int n = read_server(sock, buffer);
			if(n == 0)
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

	end_connection(sock);
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

