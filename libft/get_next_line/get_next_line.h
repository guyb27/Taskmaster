/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:54 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:54 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
