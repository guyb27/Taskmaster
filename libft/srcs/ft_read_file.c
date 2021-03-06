/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:51:40 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(char *file_path, int buff_size)
{
	int		fd;
	char	*buf;
	int		ret;

	buf = ft_memalloc((buff_size + 1) * sizeof(char));
	if ((fd = open(file_path, O_RDONLY)) == -1)
	{
		ft_putstr_fd("open() error\n", 2);
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
		free(buf);
	}
	return (0);
}
