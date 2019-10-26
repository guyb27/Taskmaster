/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   taskmaster.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 22:41:54 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 20:48:52 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TASKMASTER_H
# define TASKMASTER_H

# include "libft.h"
# include "ft_printf.h"
# include <sys/mman.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>


#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define MAX_CLIENTS 	100
#define BUF_SIZE		1024
#define PORT	 		1978


typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


typedef struct
{
   SOCKET sock;
}Client;

typedef struct		s_keyval
{
	char			*key;
	char			*value;
	struct s_keyval	*next;
}					t_keyval;

typedef struct		s_job
{
	char			name[1000];
	char			cmd[1000];
	int				nb_procs;
	char			umask[5];
	char			working_dir[1000];
	int				autostart;
	int				autorestart;
	int				exit_codes[10];
	int				start_retries;
	int				start_time;
	int				stop_time;
	int				stop_signal;
	char			stdout[1000];
	char			stderr[1000];
	t_keyval		*env;
}					t_job;

typedef struct		s_status
{
	pid_t			pid;
	enum {
		stopped,
		running,
		starting,
		paused,
		error
	}				state;
	time_t			started_time;
	time_t			stopped_time;
	int				retries;
	int				can_restart;
	struct s_status *next;
}					t_status;

typedef struct		s_shared
{
	t_status		status[500];
}					t_shared;

typedef struct		s_htime
{
	int				h;
	int				m;
	int				s;
}					t_htime;

typedef struct		s_tm
{
	t_job			jobs[1000];
	t_shared		*shared;
	int				jobs_cnt;
	char			**env;
	char			cmd[BUF_SIZE];//Modify by gmadec
	pid_t			jobs_watcher;
	char			**argv;
	char			*ret;//ADD BY GMADEC
}					t_tm;

typedef struct		s_server
{
		int socket;
		SOCKET clients[MAX_CLIENTS];
		fd_set rdfs;
}					t_server;


/*
**  ft_commands.c
*/
void				ft_cmd_start(t_tm *tm, char *name);
void				ft_cmd_pause(t_tm *tm, char *name);
void				ft_cmd_restart(t_tm *tm, char *name);
void				ft_cmd_status(t_tm *tm, char *name);
void				ft_cmd_stop(t_tm *tm, char *name);

/*
**  ft_exec_jobs.c
*/
void				ft_exec_job(t_tm *tm, int id_job, int retry);

/*
**  ft_parse_config.c
*/
void				ft_parse_config(t_tm *tm, char *config_file);

/*
**  ft_status.c
*/
void				ft_debug_status(t_status *status);
void				ft_init_status(t_status *status);
void				ft_get_job_status(t_tm *tm, int id_job, t_status *status);
void				ft_parse_config(t_tm *tm, char *config_file);

/*
**  ft_utils.c
*/
unsigned int		ft_sleep(unsigned int seconds);
void				*ft_megamalloc(int size);
void				ft_megafree(void *var, int size);
void				ft_init_job(t_job *job);
/*
**void				ft_debug_job(t_tm *tm, int job_id);
*/

/*
**	ft_jobs_funcs.c
*/
void				ft_stop_job(t_tm *tm, int id_job, t_status *status);
void				ft_restart_job(t_tm *tm, int id_job, t_status *status);
void				ft_autostart_jobs(t_tm *tm);

/*
**	ft_parse_utils.c
*/
void				ft_append_int_val(int list[], int val);
void				ft_append_env(t_job *job, char *key, char *value);

/*
**server.c
*/
t_server			init_server(char *port);
int					receive_info(SOCKET sock, char *buffer);
void				send_info(SOCKET sender, const char *buffer);

#endif
