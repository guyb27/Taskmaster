/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 11:04:32 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 04:59:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		binorfile(t_shell **ed, int *end_word)
{
	int			i;
	t_tab_lex	t;
	int			cursor;

	i = 0;
	(*ed)->t.nb_word = 0;
	while ((*ed)->t.cmd[0][i])
	{
		cursor = -1;
		t.c = (*ed)->t.cmd[0][i];
		t.i = i;
		t.count = 0;
		if (ft_isprint((*ed)->t.cmd[0][i]))
			(*ed)->t.nb_word++;
		i++;
	}
	(*ed)->t.nb_char = 1;
	*end_word = ft_strlen((*ed)->t.cmd[0]) + ft_strlen((*ed)->t.cmd[1]);
}

int				lexer_tab(t_shell **sh)
{
	int		end_word;

	if (((*sh)->t.cmd = ft_tabsplit()))
	{
		binorfile(sh, &end_word);
		if (g_cursor_pos < end_word)
		{
			g_cursor_pos = end_word;
			return (-1);
		}
		else if ((*sh)->t.cmd[1][0])
			(*sh)->t.word = ft_strdup((*sh)->t.cmd[1]);
	}
	return (1);
}

void	place_cursor_before(t_shell *sh)
{
	int		i;

	i = g_cursor_pos;
	while (g_cursor_pos)
		ft_pushed_left(sh);
	g_cursor_pos = i;
	TERMCAP("cr");
	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("dl");
		i--;
	}
}

void	place_cursor_after(t_shell *sh)
{
	int		i;

	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("al");
		i--;
	}
	ft_putstr(g_cl_prompt);
	i = g_cursor_pos;
	g_cursor_pos = 0;
	ft_reprint_cmd(sh);
	g_cursor_pos = g_cmd ? ft_strlen(g_cmd) : 0;
	while (g_cursor_pos > i)
		ft_pushed_left(sh);
	g_cursor_pos = i;
}
