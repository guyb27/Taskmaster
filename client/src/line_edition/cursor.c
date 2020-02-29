/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:20:01 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

void	ft_pushed_right(t_shell *sh)
{
	int		pos;
	int		right_xpos;
	int		zell;

	if (g_cl.cmd && g_cl.cursor_pos < (int)ft_strlen(g_cl.cmd))
	{
		pos = ft_recup_cursor_pos(sh, &zell, &right_xpos);
		if (right_xpos > 0)
			termcap("nd");
		else if (right_xpos == 0)
		{
			termcap("sf");
			termcap("cr");
		}
		g_cl.cursor_pos++;
	}
}

void	ft_pushed_left(t_shell *sh)
{
	int		pos;
	int		left_xpos;
	int		zell;

	zell = 0;
	if (g_cl.cursor_pos > 0)
	{
		pos = ft_recup_cursor_pos(sh, &left_xpos, &zell);
		if (pos == 0)
		{
			termcap("up");
			while (pos < left_xpos)
			{
				termcap("nd");
				pos++;
			}
		}
		else
			termcap("le");
		g_cl.cursor_pos--;
	}
}
