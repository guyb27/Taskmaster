/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/15 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:17:48 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

static void end_connection(int sock)
{
   closesocket(sock);
}

static void clear_clients(SOCKET *clients, int actual)
{
   int i = 0;
   for(i = 0; i < actual; i++)
   {
      closesocket(clients[i]);
   }
}

static void remove_client(SOCKET *clients, int to_remove, int *actual)
{
   /* we remove the client in the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(SOCKET));
   /* number client - 1 */
   (*actual)--;
}

static void	ft_free_env(t_keyval *env)
{
	t_keyval	*env_2;

	while (env)
	{
		env_2 = env;
		env = env->next;
		free(env_2->key);
		free(env_2->value);
		free(env_2);
	}
}

void		ft_shutdown(t_tm *tm)
{
	t_status	*tmp;
	t_status	*tmp_2;
	int			i;
	int			j;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		ft_free_env(tm->jobs[i].env);
		tmp = &tm->shared->status[i];
		j = 0;
		while (tmp)
		{
			tmp_2 = tmp;
			tmp = tmp->next;
			if (j++ > 0)
				ft_megafree(tmp_2, sizeof(t_status));
		}
	}
	ft_megafree(tm->shared, sizeof(t_shared));
	exit(0);
}


void		ft_process_cmd(t_tm *tm)
{
	printf("CMD: [%s]\n", tm->cmd);
	if (!ft_strcmp(tm->cmd, "connexion"))
		ft_sprintf(&tm->ret, "Connexion start with the server\n");
	else if (!strncmp(tm->cmd, "start", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_start(tm, tm->cmd + 6);
	else if (!strncmp(tm->cmd, "restart", 7) && (ft_strlen(tm->cmd) > 8))
		ft_cmd_restart(tm, tm->cmd + 8);
	else if (!strncmp(tm->cmd, "stop", 4) && (ft_strlen(tm->cmd) > 5))
		ft_cmd_stop(tm, tm->cmd + 5);
	else if (!strncmp(tm->cmd, "pause", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_pause(tm, tm->cmd + 6);
	else if (!strncmp(tm->cmd, "status", 6) && (ft_strlen(tm->cmd) > 7))
		ft_cmd_status(tm, tm->cmd + 7);
	else if (!strcmp(tm->cmd, "reload"))
		ft_printf("reloading config file\n");
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_printf("Quitting taskmaster\n");
		exit(0);
	}
	else if (!ft_strcmp(tm->cmd, "exit"))
		ft_shutdown(tm);
	else
		ft_sprintf(&tm->ret, "[%s]: Command not found\n", tm->cmd);
}

int			main_loop(t_server *server, t_tm *tm)
{
	
	char buffer[BUF_SIZE];
	/* the index for the array */
	int actual = 0;
	int max = server->socket;
	/* an array for all clients */
	//Client clients[MAX_CLIENTS];
	//SOCKET clients[MAX_CLIENTS];
	//fd_set rdfs;

   while (1)
   {
		ft_bzero(buffer, sizeof(buffer));
		ft_bzero(tm->cmd, sizeof(tm->cmd));
      int i = 0;
      FD_ZERO(&server->rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &server->rdfs);

      /* add the connection socket */
      FD_SET(server->socket, &server->rdfs);

      /* add socket of each client */
      for(i = 0; i < actual; i++)
      {
         FD_SET(server->clients[i], &server->rdfs);
      }

      if(select(max + 1, &server->rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      /* something from standard input : i.e keyboard */
      if(FD_ISSET(STDIN_FILENO, &server->rdfs))
      {
         /* stop process when type on keyboard */
         break;
      }
      else if(FD_ISSET(server->socket, &server->rdfs))
      {
         /* new client */
         SOCKADDR_IN csin = { 0 };
         size_t sinsize = sizeof csin;
         int csock = accept(server->socket, (SOCKADDR *)&csin, (socklen_t*)&sinsize);
         if(csock == SOCKET_ERROR)
         {
            perror("accept()");
            continue;
         }
        buffer[0] = '\0';
         /* what is the new maximum fd ? */
         max = csock > max ? csock : max;
         FD_SET(csock, &server->rdfs);
         server->clients[actual] = csock;
         actual++;
      }
      else
      {
         int i = 0;
         for(i = 0; i < actual; i++)
         {
            /* a client is talking */
            if(FD_ISSET(server->clients[i], &server->rdfs))
            {
               SOCKET client = server->clients[i];
               int c = receive_info(server->clients[i], buffer);

               /* client disconnected */
               if(c == 0)
               {
                  closesocket(server->clients[i]);
                  remove_client(server->clients, i, &actual);
               }
               else
               {
					ft_strncpy(tm->cmd, buffer, ft_strlen(buffer) - 2);
					ft_process_cmd(tm);
                	send_info(client, tm->ret);
					//free(tm->ret);
               }
               break;
            }
         }
      }
   }

   clear_clients(server->clients, actual);
   end_connection(server->socket);
   return (0);
}

int			main(int argc, char *argv[], char *env[])
{
	t_tm		tm;
	t_server	server;

	ft_bzero(&tm, sizeof(t_tm));
	tm.argv = argv;
	signal(SIGCHLD, SIG_IGN);
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2 && access(argv[1], F_OK) > -1)
	{
		ft_parse_config(&tm, argv[1]);
		ft_autostart_jobs(&tm);
		server = init_server("4242");
		main_loop(&server, &tm);
	}
	else if (access(argv[1], F_OK) == -1)
		ft_printf("error: not a valid config file\n");
	else
		ft_printf("usage: taskmaster config_file\n");
	munmap(tm.shared, sizeof(t_shared));
	return (0);
}
