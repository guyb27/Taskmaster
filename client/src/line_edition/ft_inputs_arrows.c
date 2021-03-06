/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs_arrows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:24:54 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

static int	ft_pushed_key_altup_altdown_check(t_shell *sh, char *key, int lr[2],
		int target)
{
	if (!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4) ?
												!g_cl.cursor_pos : lr[1] == -1)
	{
		termcap("rc");
		return (1);
	}
	else
	{
		if (!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4))
		{
			if (lr[0] < target)
				target = lr[0];
			ft_pushed_left(sh);
		}
		else
			ft_pushed_right(sh);
		while (ft_recup_cursor_pos(sh, &lr[0], &lr[1]) != target &&
		(!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4) ? g_cl.cursor_pos :
		lr[1] != -1 && lr[1] != 0))
			!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4) ? ft_pushed_left(sh)
														: ft_pushed_right(sh);
	}
	return (0);
}

int			ft_pushed_key_altup_altdown(t_shell *sh, char key[])
{
	int target;
	int cur_pos;
	int lr[2];

	ft_memset(lr, 0, sizeof(lr));
	cur_pos = g_cl.cursor_pos;
	termcap("sc");
	target = ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	while (!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4) ?
	g_cl.cursor_pos && lr[1] != 0 : (lr[1] != -1 && lr[1] != 0))
	{
		!ft_strncmp((char[4]){27, 27, 91, 65}, key, 4) ?
		ft_pushed_left(sh) : ft_pushed_right(sh);
		ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	}
	if (ft_pushed_key_altup_altdown_check(sh, key, lr, target))
		g_cl.cursor_pos = cur_pos;
	return (0);
}

int			ft_pushed_key_altleft_altright(t_shell *sh, char key[])
{
	int i;

	i = g_cl.cursor_pos;
	while (!ft_strncmp((char[4]){27, 27, 91, 68}, key, 4) ? i > 0 : i <
			(int)ft_strlen(g_cl.cmd))
	{
		if ((i == 0 || ft_isspace(g_cl.cmd[i - 1])) &&
	!ft_isspace(g_cl.cmd[i]) && ft_isprint(g_cl.cmd[i]) && i != g_cl.cursor_pos)
			break ;
		!ft_strncmp((char[4]){27, 27, 91, 68}, key, 4) ? i-- : i++;
	}
	if (!((i == 0 || ft_isspace(g_cl.cmd[i - 1])) && !ft_isspace(g_cl.cmd[i]) &&
				ft_isprint(g_cl.cmd[i]) && i != g_cl.cursor_pos))
		return (0);
	while (g_cl.cursor_pos != i)
		!ft_strncmp((char[4]){27, 27, 91, 68}, key, 4) ?
		ft_pushed_left_right(sh, (char[4]){27, 91, 68, 0}) :
		ft_pushed_left_right(sh, (char[4]){27, 91, 67, 0});
	return (0);
}

int			ft_pushed_left_right(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	else if (!ft_strcmp((char[4]){27, 91, 68, 0}, key))
		ft_pushed_left(sh);
	else if (!ft_strcmp((char[4]){27, 91, 67, 0}, key))
		ft_pushed_right(sh);
	return (0);
}

int			ft_pushed_up_down(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	else
		history_get(sh, key);
	return (0);
}
