/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 11:04:32 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 09:18:17 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			binorfile(t_shell **ed, int *end_word)
{
	int			i;
	t_tab_lex	t;

	i = 0;
	(*ed)->t.nb_word = 0;
	while ((*ed)->t.cmd[0][i])
	{
		t.c = (*ed)->t.cmd[0][i];
		t.i = i;
		t.count = 0;
		if (ft_isprint((*ed)->t.cmd[0][i]) && !ft_isblank((*ed)->t.cmd[0][i]))
		{
			(*ed)->t.nb_word++;
			while (ft_isprint((*ed)->t.cmd[0][i]) &&
					!ft_isblank((*ed)->t.cmd[0][i]))
				i++;
		}
		else
			i++;
	}
	(*ed)->t.nb_char = 1;
	*end_word = ft_strlen((*ed)->t.cmd[0]) + ft_strlen((*ed)->t.cmd[1]);
}

void			place_cursor_before(t_shell *sh)
{
	int			i;

	i = g_cl.cursor_pos;
	while (g_cl.cursor_pos)
		ft_pushed_left(sh);
	g_cl.cursor_pos = i;
	TERMCAP("cr");
	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("dl");
		i--;
	}
}

void			place_cursor_after(t_shell *sh)
{
	int			i;

	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("al");
		i--;
	}
	ft_putstr(g_cl.prompt);
	i = g_cl.cursor_pos;
	g_cl.cursor_pos = 0;
	ft_reprint_cmd(sh);
	g_cl.cursor_pos = g_cl.cmd ? ft_strlen(g_cl.cmd) : 0;
	while (g_cl.cursor_pos > i)
		ft_pushed_left(sh);
	g_cl.cursor_pos = i;
}
