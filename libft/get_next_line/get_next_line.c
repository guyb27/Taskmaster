/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:54 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:54 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		**ft_get_saved(t_multi_fd **fd_list, int fd)
{
	t_multi_fd	*new;
	t_multi_fd	*tmp;

	if (*fd_list)
	{
		tmp = *fd_list;
		while (tmp->next && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd == fd)
			return (&tmp->saved);
	}
	if (!(new = (t_multi_fd*)malloc(sizeof(t_multi_fd))))
		return (NULL);
	new->fd = fd;
	new->saved = NULL;
	new->next = NULL;
	if (*fd_list)
		tmp->next = new;
	else
		*fd_list = new;
	return (&new->saved);
}

static void		ft_read_buf(char **saved, char *buf)
{
	char	*tmp;

	if (*saved)
	{
		tmp = ft_strdup(*saved);
		free(*saved);
		*saved = ft_strjoin(tmp, buf);
		free(tmp);
	}
	else
		*saved = ft_strdup(buf);
}

static void		ft_get_saved_line(char **saved, char **line)
{
	char	*tmp;
	char	*eol;
	size_t	eol_dist;

	eol = ft_strchr(*saved, '\n');
	eol_dist = ft_abs(eol - *saved);
	tmp = ft_strdup(*saved);
	free(*saved);
	if (eol_dist <= ft_strlen(tmp))
		*saved = ft_strsub(tmp, eol_dist + 1, ft_strlen(tmp));
	else
		*saved = ft_strdup("");
	*line = ft_strsub(tmp, 0, eol_dist);
	free(tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_multi_fd	*fd_list = NULL;
	char				**saved;
	char				buf[BUFF_SIZE + 1];
	int					ret;
	int					readed;

	if (fd < 0 || !line || (read(fd, NULL, 0) < 0))
		return (-1);
	saved = ft_get_saved(&fd_list, fd);
	ret = 0;
	readed = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		readed = 1;
		ft_read_buf(saved, buf);
		if (ft_strchr(*saved, '\n'))
			break ;
	}
	if (*saved && *saved[0] && !ret && !readed)
		readed = 1;
	if (*saved)
		ft_get_saved_line(saved, line);
	return (ret == -1 ? -1 : readed);
}
