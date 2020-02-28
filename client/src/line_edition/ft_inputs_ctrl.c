/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:10 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

int		ft_pushed_key_ctrl_c(t_shell *sh, char key[])
{
	(void)key;
	ft_pushed_key_home_end(sh, FT_KEY_END);
	TERMCAP("do");
	TERMCAP("cr");
	get_term_raw_mode(0);
	ft_strdel(&g_cl.cmd);
	return (1);
}

int		ft_pushed_key_ctrl_d(t_shell *sh, char key[])
{
	(void)key;
	(void)sh;
	if (!g_cl.cmd)
	{
		get_term_raw_mode(0);
		g_cl.cmd = ft_strdup(FT_KEY_CTRL_D);
		ft_putstr("\n");
		return (1);
	}
	return (0);
}

int		ft_pushed_key_ctrl_l(t_shell *sh, char key[])
{
	(void)sh;
	(void)key;
	ft_handle_resize(0);
	return (0);
}
