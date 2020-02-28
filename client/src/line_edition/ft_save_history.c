/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:10 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

static int	save_to_file(char **histsave, char *path)
{
	int		fd;
	int		i;

	i = -1;
	fd = -1;
	if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
		return (EXIT_FAILURE);
	if (histsave)
		while (histsave[++i])
			ft_putendl_fd(histsave[i], fd);
	return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void	add_memory(char *news, char ***histsave)
{
	char	*s;
	char	tmp[ft_strlen(news) + 1];
	int		histfilesize;

	s = *histsave ? ft_strdup((*histsave)[ft_tablen(*histsave) - 1]) : NULL;
	ft_bzero(tmp, sizeof(tmp));
	ft_strncpy(tmp, news, ft_strlen(news) - 1);
	if ((!*histsave || ft_strcmp(s, tmp)) && HISTSIZE > 0)
	{
		histfilesize = *histsave ? ft_tablen(*histsave) + 1 : 1;
		while (--histfilesize >= HISTSIZE && histfilesize >= 0)
			ft_strdel_in_tab(histsave, 0);
		ft_malloc_cmd(histsave, tmp);
	}
	ft_strdel(&s);
}

void		history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;

	if (version == -1)
	{
		path = ft_strdup(s);
		histsave = ft_tabdup(*history);
	}
	else if (version == 0 && histsave)
		*history = ft_tabdup(histsave);
	else if (version == 1 && news)
		add_memory(news, &histsave);
	else if (version == 2)
	{
		tmp = ft_strjoin(path, HISTFILE);
		save_to_file(histsave, tmp);
		ft_tabdel(&histsave);
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}
