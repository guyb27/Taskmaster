/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read_file.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:19 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:21:54 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
