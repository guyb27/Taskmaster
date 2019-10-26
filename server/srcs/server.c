
#include "taskmaster.h"

t_server	init_server(char *port)
{
    t_server    server;
   SOCKADDR_IN sin = { 0 };

    ft_bzero(&server, sizeof(t_server));
    server.socket = socket(AF_INET, SOCK_STREAM, 0);
   if(server.socket == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }
   sin.sin_addr.s_addr = inet_addr("127.0.0.1");
   sin.sin_port = htons(PORT);
   sin.sin_family = AF_INET;
   if(bind(server.socket,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }
   if(listen(server.socket, MAX_CLIENTS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }
   return (server);
}

int			receive_info(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = '\0';
   printf("BUF[%s], N: [%d] \n", buffer, n);
   //ft_strncpy(buffer, buffer, ft_strlen(buffer) - 1);
   //buffer[ft_strlen(buffer) - 1] = '\0';

   return n;
}


static void write_client(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}


void		send_info(SOCKET sender, const char *buffer)
{
   int i;
   char message[BUF_SIZE];

   message[0] = 0;
   i = 0;
   strcpy(message, buffer);
   //strcpy(message, "Hello World !\n");
   write_client(sender, message);
}