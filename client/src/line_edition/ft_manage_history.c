/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs_arrows.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 15:56:11 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 09:25:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		advanced_history(char ***history, char *base)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	while ((*history)[++i])
		if (!ft_strncmp(base, (*history)[i], ft_strlen(base)))
			ft_malloc_cmd(&tmp, (*history)[i]);
	ft_tabdel(history);
	if (tmp)
		*history = ft_tabdup(tmp);
	ft_tabdel(&tmp);
	return (0);
}

static void		the_last_of_dowm(t_shell *sh)
{
	sh->hist = -2;
	ft_pushed_key_home_end(sh, FT_KEY_HOME);
	TERMCAP("cd");
	ft_strdel(&g_cl.cmd);
	if (sh->tmp_line)
	{
		g_cl.cmd = ft_strdup(sh->tmp_line);
		ft_strdel(&sh->tmp_line);
		ft_putstr(g_cl.cmd);
	}
	g_cl.cursor_pos = g_cl.cmd ? ft_strlen(g_cl.cmd) : 0;
}

static void		heart_of_hist_search(t_shell *sh, char **history, char key[])
{
	if (sh->hist == -2)
		sh->hist = -1;
	if (key[2] == 65)
		sh->hist++;
	else
		sh->hist--;
	ft_pushed_key_home_end(sh, FT_KEY_HOME);
	TERMCAP("cd");
	if (sh->hist >= 0)
	{
		ft_strdel(&g_cl.cmd);
		g_cl.cmd = ft_strdup(history[sh->hist]);
		ft_putcmd(sh, ft_strlen(g_cl.cmd));
	}
}

void			history_get(t_shell *sh, char key[])
{
	char		**history;

	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	if (history && key[2] == 65 && sh->hist == -2 && g_cl.cmd)
		sh->tmp_line = ft_strdup(g_cl.cmd);
	if (history && sh->tmp_line)
		advanced_history(&history, sh->tmp_line);
	if (history)
	{
		if ((sh->hist + 1 < ft_tablen(history) && key[2] == 65) ||
			(sh->hist >= 0 && key[2] == 66) || (sh->hist == -2 && key[2] == 65))
			heart_of_hist_search(sh, history, key);
		if (key[2] == 66 && sh->hist == -1 && g_cl.cmd)
			the_last_of_dowm(sh);
		ft_tabdel(&history);
	}
	else
		ft_strdel(&sh->tmp_line);
}
