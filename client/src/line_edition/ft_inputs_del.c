/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:10 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

int		ft_pushed_key_backspace(t_shell *sh, char key[])
{
	int		tmp_cursor;

	(void)key;
	if (g_cl.cmd && g_cl.cursor_pos > 0)
	{
		tmp_cursor = g_cl.cursor_pos;
		while (g_cl.cursor_pos)
			ft_pushed_left(sh);
		ft_chardel_at(&g_cl.cmd, tmp_cursor - 1);
		TERMCAP("cd");
		if (g_cl.cmd)
		{
			ft_reprint_cmd(sh);
			g_cl.cursor_pos = ft_strlen(g_cl.cmd);
			while (g_cl.cursor_pos >= tmp_cursor)
				ft_pushed_left(sh);
		}
	}
	return (0);
}

int		ft_pushed_key_del(t_shell *sh, char key[])
{
	int		tmp_cursor;

	(void)key;
	if (g_cl.cmd && g_cl.cursor_pos >= 0 &&
			g_cl.cursor_pos != (int)ft_strlen(g_cl.cmd))
	{
		tmp_cursor = g_cl.cursor_pos;
		while (g_cl.cursor_pos)
			ft_pushed_left(sh);
		ft_chardel_at(&g_cl.cmd, tmp_cursor);
		TERMCAP("cd");
		if (g_cl.cmd)
		{
			ft_reprint_cmd(sh);
			g_cl.cursor_pos = ft_strlen(g_cl.cmd);
			while (g_cl.cursor_pos > tmp_cursor)
				ft_pushed_left(sh);
		}
	}
	return (0);
}
