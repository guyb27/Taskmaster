/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:00:22 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:00:22 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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

typedef struct	s_srv_cmd
{
	char		cmd[100];
	int			arg;
}				t_srv_cmd;

typedef struct	s_cl
{
	char		*cmd;
	int			cursor_pos;
	char		*prompt;
	t_srv_cmd	cmd_struct[100];
	char		process[100][100];
}				t_cl;

t_cl			g_cl;

int				heart_of_101sh(char *line, int fd_base);
void			signal_shell(void);
void			exit_shell(void);

int				read_server(int sock, char *buffer);
int				write_server(int sock, const char *buffer);
int				ft_init_parse(int sock);
void			ft_get_tab_elems(char *str);

#endif
