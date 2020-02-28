/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 07:29:22 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

int		ft_input_check(char key[], char buf[])
{
	if (!strncmp(key, buf, 4) ||
	(!strncmp(key, buf, 2) && key[2] == -101 && buf[2] >= 65 && buf[2] <= 66) ||
	(!strncmp(key, buf, 2) && key[2] == -102 && buf[2] >= 67 && buf[2] <= 68) ||
	(!strncmp(key, buf, 3) && key[3] == -101 && buf[3] >= 65 && buf[3] <= 66) ||
	(!strncmp(key, buf, 3) && key[3] == -102 && buf[3] >= 67 && buf[3] <= 68) ||
	(!strncmp(key, buf, 2) && key[2] == -103 && buf[2] >= 70 && buf[2] <= 72))
		return (1);
	return (0);
}

void	ft_init_input_keys(t_shell *sh)
{
	ft_memcpy(sh->keys[0].key, (char[4]){127, 0, 0, 0}, 4);
	sh->keys[0].f = &ft_pushed_key_backspace;
	ft_memcpy(sh->keys[1].key, (char[4]){10, 0, 0, 0}, 4);
	sh->keys[1].f = &ft_pushed_key_enter;
	ft_memcpy(sh->keys[2].key, FT_KEY_LEFTRIGHT, 4);
	sh->keys[2].f = &ft_pushed_left_right;
	ft_memcpy(sh->keys[3].key, FT_KEY_UPDOWN, 4);
	sh->keys[3].f = &ft_pushed_up_down;
	ft_memcpy(sh->keys[4].key, (char[4]){3, 0, 0, 0}, 4);
	sh->keys[4].f = &ft_pushed_key_ctrl_c;
	ft_memcpy(sh->keys[5].key, (char[4]){4, 0, 0, 0}, 4);
	sh->keys[5].f = &ft_pushed_key_ctrl_d;
	ft_memcpy(sh->keys[6].key, (char[4]){12, 0, 0, 0}, 4);
	sh->keys[6].f = &ft_pushed_key_ctrl_l;
	ft_memcpy(sh->keys[7].key, (char[4]){9, 0, 0, 0}, 4);
	sh->keys[7].f = &ft_pushed_key_tab;
	ft_memcpy(sh->keys[8].key, (char[4]){27, 91, 51, 126}, 4);
	sh->keys[8].f = &ft_pushed_key_del;
	ft_memcpy(sh->keys[9].key, FT_KEY_ALT_UD, 4);
	sh->keys[9].f = &ft_pushed_key_altup_altdown;
	ft_memcpy(sh->keys[10].key, FT_KEY_ALT_LR, 4);
	sh->keys[10].f = &ft_pushed_key_altleft_altright;
	ft_memcpy(sh->keys[11].key, FT_KEY_HOME_END, 4);
	sh->keys[11].f = &ft_pushed_key_home_end;
	sh->keys[12].f = NULL;
}

int		ft_pushed_key_home_end(t_shell *sh, char key[])
{
	if (!ft_strcmp((char[4]){27, 91, 72, 0}, key))
		while (g_cl.cursor_pos > 0)
			ft_pushed_left_right(sh, (char[4]){27, 91, 68, 0});
	if (!ft_strcmp((char[4]){27, 91, 70, 0}, key))
		while (g_cl.cursor_pos < (int)ft_strlen(g_cl.cmd))
			ft_pushed_left_right(sh, FT_KEY_RIGHT);
	return (0);
}

int		ft_pushed_key_enter(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	ft_pushed_key_home_end(sh, (char[4]){27, 91, 70, 0});
	if (g_cl.cmd && ft_str_isblank(g_cl.cmd))
	{
		free(g_cl.cmd);
		g_cl.cmd = ft_strdup("\n");
	}
	else
		g_cl.cmd = ft_strjoin_free(g_cl.cmd, "\n");
	get_term_raw_mode(0);
	write(1, "\n", 1);
	return (1);
}

int		ft_pushed_key_tab(t_shell *sh, char key[])
{
	tabulator(&sh, 1, key);
	return (0);
}
