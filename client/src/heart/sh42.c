/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 04:55:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		ft_putnbr_hex(int octet, int rem)
{
	char base[17];

	ft_strcpy(base, "0123456789abcdef");
	if (rem > 1)
		ft_putnbr_hex(octet >> 4, rem - 1);
	write(1, base + (octet % 16), 1);
}

static void		ft_print_mem_hex(void *addr, unsigned int size, unsigned int a)
{
	unsigned int b;

	b = -1;
	while (++b < 16)
	{
		if ((a + b) < size)
			ft_putnbr_hex(*((unsigned char*)addr + a + b), 2);
		else
			ft_putstr("  ");
		if (b % 2)
			ft_putchar(' ');
	}
}

static void		ft_print_mem_str(void *addr, unsigned int size, unsigned int a)
{
	unsigned int b;

	b = -1;
	while (++b < 16 && (a + b) < size)
		if (ft_isprint(*((char*)addr + a + b)))
			ft_putchar(*((char*)addr + a + b));
		else
			ft_putchar('.');
}

void			*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int a;

	a = 0;
	while (a < size)
	{
		ft_putnbr_hex(*(int*)addr + a, 8);
		ft_putstr(": ");
		ft_print_mem_hex(addr, size, a);
		ft_putchar(' ');
		ft_print_mem_str(addr, size, a);
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}

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


static int init_connection(const char *address)
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
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		perror("connect()");
		exit(errno);
	}

	return sock;
}

void stackchar(char c)
{
	if (ioctl(0, TIOCSTI, &c) < 0) {
		perror("ioctl");
		exit(1);
	}
}

int get_fd( void *ptr, size_t size )
{
    unsigned char *p = ptr ;
	int				mult = 1;
	int ret = 0;

    for( size_t i = 0; i < size; i++ )
    {
        for( short j = 0; j <= 7; j++ )
        {
			ret += ((p[i] >> j) & 1) * mult;
			mult *= 2;
        }
    }
	return (ret);
}

static void *disconnect_srv (void *p_data)
{
	char ret[50000];
	char prompt[5000];
	int sock;
	int ret_srv = 0;

	sock = get_fd(p_data, sizeof(int));
	while (1)
	{
		ft_memset(ret, 0, sizeof(ret));
		if ((ret_srv = read_server(sock, ret)) == 0)
		{
			printf("Server disconnected !\n");
			g_stop_srv = -1;
			stackchar('\n');
			end_connection(sock);
			get_term_raw_mode(0);
			return (NULL);
		}
		else if (ret_srv > 0)
		{
			ft_memset(prompt, 0, sizeof(prompt));
			g_stop_srv = 1;
			get_term_raw_mode(0);
			ft_putstr(ret);
			get_term_raw_mode(1);
			g_stop_srv = 0;
		}
		else
		{
			printf("ERR[0][%d]\n", ret_srv);
			printf("ERR[1][%d]\n", ret_srv);
		}
	}
			printf("DISCONNECT SRV\n");
	return NULL;
}

static int		shell(const char *addr, const char *port)
{
	int sock = init_connection(addr);
	char buffer[BUF_SIZE];
	char prompt[500];
	fd_set rdfs;
	ft_print_logo_and_init();
	int i = 0;
	int ret = 0;
	pthread_t thread_store;

	ft_memset(prompt, 0, sizeof(prompt));
	if ((i = read_server(sock, prompt)) == 0)
	{
		printf("Server disconnected !\n");
		end_connection(sock);
		return (0);
	}
	ft_putstr(prompt);
	g_cl_prompt = ft_strdup(prompt);
	ret = pthread_create(&thread_store, NULL, disconnect_srv, (void*)&sock);
	while(1)
	{
		ft_memset(buffer, 0, sizeof(buffer));
		ft_get_user_input();
		get_term_raw_mode(0);
		if (g_cmd && !ft_strncmp(FT_KEY_CTRL_D, g_cmd, 4))
		{
			ft_strdel(&g_cmd);
			pthread_exit(&ret);
			end_connection(sock);
			return (0);
		}
		else if (g_cmd && g_cmd[0])
		{
			history_save((char ***)NULL, g_cmd, 1, (char *)NULL);
			g_stop_srv = 1;
			write_server(sock, g_cmd);
			if (!ft_strcmp("exit\n", g_cmd))
			{
				pthread_exit(&ret);
				end_connection(sock);
				ft_strdel(&g_cmd);
				return (0);
			}
		}
		ft_strdel(&g_cmd);
		i = 1;
	}
	pthread_exit(&ret);
	end_connection(sock);
	return (0);
}
int				main(int ac, const char **av)
{
	int		ret;

	if (ac < 2) {
		fprintf(stderr, "Usage: %s <host> <port>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (init_shell(ac, av))
	{
		ft_putstr("Taskmaster can't run in non-interactive mode.");
		return (EXIT_FAILURE);
	}
	ret = shell(av[1], av[2]);
	exit_shell();
	return (ret);
}
