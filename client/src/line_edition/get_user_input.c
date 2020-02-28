/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:10 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:10 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

int			ft_recup_cursor_pos(t_shell *sh, int *left_xpos, int *right_xpos)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	*left_xpos = 0;
	*right_xpos = -1;
	while (i < g_cl.cursor_pos + sh->prompt_len)
	{
		ret = ret + 1 == sh->ws.ws_col || (i > sh->prompt_len &&
				g_cl.cmd[i - sh->prompt_len] == '\n') ? ret = 0 : ret + 1;
		if (i == g_cl.cursor_pos + sh->prompt_len - 2)
			*left_xpos = ret;
		i++;
	}
	if (g_cl.cmd && g_cl.cursor_pos < (int)ft_strlen(g_cl.cmd))
		*right_xpos = ret + 1 == sh->ws.ws_col || (i > sh->prompt_len &&
			g_cl.cmd[i - sh->prompt_len] == '\n') ? 0 : ret + 1;
	return (ret);
}

int			ft_reprint_cmd(t_shell *sh)
{
	int		i;
	int		cursor_in_line;

	ft_get_cols(&sh->ws);
	i = g_cl.cursor_pos;
	cursor_in_line = ft_recup_cursor_pos(sh, &cursor_in_line, &cursor_in_line);
	while (g_cl.cmd && g_cl.cmd[i])
	{
		if (!(g_cl.cmd[i] == '\n'))
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar);
			write(1, &g_cl.cmd[i], 1);
			tputs(tgetstr("ei", NULL), 1, ft_putchar);
		}
		if (g_cl.cmd[i] == '\n' || (cursor_in_line + 1) % sh->ws.ws_col == 0)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			cursor_in_line = 0;
		}
		else
			cursor_in_line++;
		i++;
	}
	return (i);
}

static void	ft_insert_to_line(t_shell *sh, char *buff)
{
	int		i;
	int		cursor_max;
	int		cursor_tmp;

	i = -1;
	while (buff[++i])
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_add_to_str(&g_cl.cmd, buff[i], g_cl.cursor_pos);
		cursor_max = ft_reprint_cmd(sh);
		cursor_tmp = g_cl.cursor_pos;
		g_cl.cursor_pos = cursor_max;
		while (--cursor_max > cursor_tmp)
			ft_pushed_left(sh);
		g_cl.cursor_pos = cursor_tmp + 1;
	}
}

static int	ft_get_user_input_buff_checker(t_shell *sh, char *buff)
{
	int		i;

	i = -1;
	if (ft_isprint(buff[0]) || (buff[0] < 0 && (int)buff < 0x10FFFF))
	{
		init_tab_and_hist(sh, buff);
		ft_insert_to_line(sh, buff);
	}
	else
	{
		init_tab_and_hist(sh, buff);
		while (sh->keys[++i].f)
			if (ft_input_check(sh->keys[i].key, buff) &&
					sh->keys[i].f(sh, buff))
			{
				tputs(tgetstr("ve", NULL), 1, ft_putchar);
				return (1);
			}
	}
	return (0);
}

char		*ft_get_user_input(void)
{
	t_shell	sh;
	char	buff[5];

	ft_memset(&sh, 0, sizeof(sh));
	if (ft_init_shell_struct(&sh) == -1)
		return (g_cl.cmd = ft_strdup("exit\n"));
	sh.prompt_len = 13;
	ft_init_input_keys(&sh);
	while (1)
	{
		ft_bzero(buff, 5);
		if (!(read(0, buff, 4)))
			return (NULL);
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		ft_get_cols(&sh.ws);
		if (ft_get_user_input_buff_checker(&sh, buff))
		{
			if (!g_cl.cmd || !ft_strcmp("\n", g_cl.cmd))
				ft_putstr(g_cl.prompt);
			return (g_cl.cmd);
		}
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
	}
}
