/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 20:37:59 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 14:52:29 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 3

# include "../srcs/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct			s_multi_fd
{
	int					fd;
	char				*saved;
	struct s_multi_fd	*next;
}						t_multi_fd;

int						get_next_line(const int fd, char **line);

#endif
