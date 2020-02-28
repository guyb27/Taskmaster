/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:42 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:54:42 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

int			search_bin_tab(t_shell **ed)
{
	int		i;

	i = 0;
	while (g_cl.cmd_struct[i].cmd[0])
	{
		if (!(*ed)->t.word || !ft_strncmp((*ed)->t.word,
		g_cl.cmd_struct[i].cmd, ft_strlen((*ed)->t.word)))
			ft_malloc_cmd(&(*ed)->t.elem, g_cl.cmd_struct[i].cmd);
		i++;
	}
	return (0);
}

int			search_in_rep_tab(t_shell **ed)
{
	int		i;
	int		found;
	char	**cmd;

	i = -1;
	found = 0;
	cmd = ft_strsplit((*ed)->t.cmd[0], ' ');
	while (!found && g_cl.cmd_struct[++i].cmd[0])
		if (!ft_strcmp(g_cl.cmd_struct[i].cmd, cmd[0]) &&
				g_cl.cmd_struct[i].arg)
			found = g_cl.cmd_struct[i].arg;
	i = -1;
	while (found && g_cl.process[++i][0])
		if (!(*ed)->t.word ||
		!ft_strncmp((*ed)->t.word, g_cl.process[i], ft_strlen((*ed)->t.word)))
			ft_malloc_cmd(&(*ed)->t.elem, g_cl.process[i]);
	if (found == 2 && (!(*ed)->t.word ||
		!ft_strncmp((*ed)->t.word, "all", ft_strlen((*ed)->t.word))))
		ft_malloc_cmd(&(*ed)->t.elem, "all");
	return (ft_tabdel(&cmd));
}

int			ft_search_big_param(t_line *line)
{
	t_line	*tmp;
	size_t	len_max;

	len_max = 0;
	tmp = line;
	while (tmp)
	{
		if (ft_strlen(tmp->elem) > len_max)
			len_max = ft_strlen(tmp->elem);
		tmp = tmp->next;
	}
	return (len_max);
}
