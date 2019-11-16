/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heart.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 01:40:43 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 06:36:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HEART_H
# define HEART_H

# define BUFF_SIZE 4096
# define BI_MAX 4084
# define MAX_HASH 100
# include <unistd.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/utsname.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <netdb.h>
# include <string.h>
# include <time.h>
# include <curses.h>
# include <fcntl.h>
# include <dirent.h>
# include <pwd.h>
# include <limits.h>
# include "../libft/include/libft.h"
# include "init.h"
# include "ft_select.h"
# include "line_edition.h"
# include <errno.h>
# include <netdb.h>
# include <pthread.h>

# define BUF_SIZE 1024

int				g_interupt;
char			*g_cmd;
int				g_cursor_pos;
char			*g_cl_prompt;

typedef struct	s_srv_cmd
{
	char		cmd[100];
	int			arg;
}				t_srv_cmd;

typedef struct	s_srv_tab
{
	t_srv_cmd	cmd[100];
	char		process[100][100];
}				t_srv_tab;

t_srv_tab		g_tab;

int				heart_of_101sh(char *line, int fd_base);
void			signal_shell(void);
void			exit_shell(void);

void			ft_handle_resize(int sig);
void			ft_handle_sigint(int sig);
int				read_server(int sock, char *buffer);
int				write_server(int sock, const char *buffer);
int				ft_init_parse(int sock);
void			ft_get_tab_elems(char *str);

#endif
