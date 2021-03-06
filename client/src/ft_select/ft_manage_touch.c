/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_touch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:41 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:54:41 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	is_arrows(char *s)
{
	if ((s[0] == 27 && s[1] == 91 && s[2] >= 65 && s[2] <= 68) ||
			(s[0] == 9 && s[1] == 0))
		return (1);
	return (0);
}

int			replace_line_after_tab(t_shell **ed)
{
	int		i;
	char	*tmp;

	i = -1;
	if ((*ed)->t.before)
	{
		tmp = (*ed)->sel->ret ? ft_strjoin((*ed)->t.before, (*ed)->sel->ret)
			: ft_strdup((*ed)->t.before);
		ft_strdel(&(*ed)->sel->ret);
		(*ed)->sel->ret = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&(*ed)->t.cmd[1]);
	(*ed)->t.cmd[1] = (*ed)->sel->ret;
	g_cl.cursor_pos = ft_strlen((*ed)->t.cmd[0]) + ft_strlen((*ed)->t.cmd[1]);
	ft_strdel(&g_cl.cmd);
	ft_concat_tab_to_str((*ed)->t.cmd, &g_cl.cmd);
	return (0);
}

int			ft_attrib_line(t_shell **ed)
{
	t_line		*line;

	line = (*ed)->sel->line;
	if (line->cursor_inside == 0)
		while (line->cursor_inside == 0)
			line = line->next;
	(*ed)->sel->ret = ft_strdup(line->elem);
	replace_line_after_tab(ed);
	return (0);
}

int			ft_manage_touch(t_shell **ed, int version, char key[])
{
	if (version == 0)
		return (ft_attrib_line(ed));
	else if (is_arrows(key))
	{
		ft_arrows(key[0] == 9 ? 66 : key[2], &(*ed)->sel, &(*ed)->tabu);
		return (ft_attrib_line(ed) + 1);
	}
	else if (key[0] == 10)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		return (ft_attrib_line(ed) + 4);
	}
	return (-1);
}
