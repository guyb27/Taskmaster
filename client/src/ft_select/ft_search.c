/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:56:07 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 08:57:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		search_bin_tab(t_shell **ed)
{
	int		i = 0;

	while (g_tab.cmd[i].cmd[0])
	{
		if (!(*ed)->t.word ||
		!ft_strncmp((*ed)->t.word, g_tab.cmd[i].cmd, ft_strlen((*ed)->t.word)))
			ft_malloc_cmd(&(*ed)->t.elem, g_tab.cmd[i].cmd);
		i++;
	}
	return (0);
}

int		search_in_rep_tab(t_shell **ed)
{
	int		i;
	int		found;
	char **cmd;

	i = 0;
	found = 0;
	cmd = ft_strsplit((*ed)->t.cmd[0], ' ');
	while (!found && g_tab.cmd[i].cmd[0])
		if ((i++) && !ft_strcmp(g_tab.cmd[i].cmd, cmd[0]) && g_tab.cmd[i].arg)
			found = g_tab.cmd[i].arg;
	i = 0;
	while (found && g_tab.process[i][0])
	{
		if (!(*ed)->t.word ||
		!ft_strncmp((*ed)->t.word, g_tab.process[i], ft_strlen((*ed)->t.word)))
			ft_malloc_cmd(&(*ed)->t.elem, g_tab.process[i]);
		i++;
	}
	if (found == 2 && (!(*ed)->t.word ||
		!ft_strncmp((*ed)->t.word, "all", ft_strlen((*ed)->t.word))))
		ft_malloc_cmd(&(*ed)->t.elem, "all");
	ft_tabdel(&cmd);
	return (0);
}

char	**search_var_tab(char *word)
{
	char	**ret;


	ret = NULL;
	ft_malloc_cmd(&ret, "HELLO WORLD");
	ft_malloc_cmd(&ret, "HELLO");
	return (ret);
}

int		ft_search_big_param(t_line *line)
{
	t_line		*tmp;
	size_t		len_max;

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
