/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:39:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_logx(int log_level, char *msg, char *x)
{
		ft_log_var(log_level, FUNC, msg""KRESET, (void*)(size_t)x);
}

char	*ft_read_file(char *file_path, int buff_size)
{
	int		fd;
	char	*buf;
	int		ret;

	buf = ft_memalloc((buff_size + 1) * sizeof(char));
	if ((fd = open(file_path, O_RDONLY)) == -1)
	{
		ft_putstr_fd("open() error\n", 2);
		LOGX(ERROR, "open() error [%s]\n", file_path);
		free(buf);
	}
	while ((ret = read(fd, buf, buff_size)))
	{
		buf[ret] = '\0';
		return (buf);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("close() error\n", 2);
		LOGX(ERROR, "close() error [%s]\n", file_path);
		free(buf);
	}
	return (0);
}
