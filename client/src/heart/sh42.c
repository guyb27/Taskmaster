/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 03:11:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"


static void		ft_print_logo_and_init(void)
{
	g_cmd = NULL;
	g_prompt = PROMPT;
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

static int		shell(const char *addr, const char *port)
{
	char buf[BUF_SIZE];

	int sock = init_connection(addr);
	char buffer[BUF_SIZE];
	fd_set rdfs;

	ft_print_logo_and_init();
   while(1)
   {

      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add the socket */
      FD_SET(sock, &rdfs);

      if(select(sock, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

	printf("[0]\n\r");
      /* something from standard input : i.e keyboard */
      if(FD_ISSET(STDIN_FILENO, &rdfs))
      {
		ft_memset(buf, 0, sizeof(buf));
		ft_get_user_input(&g_prompt);
		if (g_cmd && g_prompt == PROMPT && !ft_strncmp(FT_KEY_CTRL_D, g_cmd, 4))
			return (0);
		else if (g_cmd && g_cmd[1])
		{
			history_save((char ***)NULL, g_cmd, 1, (char *)NULL);
         	write_server(sock, g_cmd);
		}
		ft_strdel(&g_cmd);
      }
      else if(FD_ISSET(sock, &rdfs))
      {
         int n = read_server(sock, buffer);
         /* server down */
         if(n == 0)
         {
            printf("Server disconnected !\n");
            break;
         }
         printf("%s\n", buffer);
      }
   }

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