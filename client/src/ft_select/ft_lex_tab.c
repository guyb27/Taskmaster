/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lex_tab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 01:57:51 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 10:22:27 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		lex_word(const char *s, int i, int *find, int *cursor)
{
	int			count;

	count = 0;
	while (ft_isprint(s[i]) && !ft_isblank(s[i]) && s[i])
	{
		if ((i == *cursor || i + 1 == *cursor) && *find != -1)
		{
			*find = 1;
			*cursor = -1;
		}
		i++;
		count++;
	}
	return (count);
}

static int		lex_blank(const char *s, int i, int *find, int *cursor)
{
	int			count;

	count = 0;
	if (ft_isblank(s[i]) && i != *cursor)
	{
		while (ft_isblank(s[i]) && s[i] && i != *cursor)
		{
			if (i == *cursor && *find != -1)
			{
				*find = 2;
				*cursor = -1;
				break ;
			}
			i++;
			count++;
		}
	}
	else if (i == *cursor)
	{
		*cursor = -1;
		if (*find != -1)
			*find = 2;
	}
	return (count);
}

int				lex_tab(const char *s, int i, int *find, int *cursor)
{
	t_tab_lex	t;

	t.c = s[i];
	t.i = i;
	t.count = 0;
	if (ft_isblank(s[i]))
		return (lex_blank(s, i, find, cursor));
	else if (ft_isprint(s[i]) && !ft_isblank(s[i]))
		return (lex_word(s, i, find, cursor));
	return (0);
}

int				lexer_tab(t_shell **sh)
{
	int			end_word;

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
