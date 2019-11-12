/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs_arrows.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 15:56:11 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 05:49:01 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"


static int	save_to_file(char **histsave, char *path)
{
	int		fd;
	int		i;

	i = -1;
	fd = -1;
	if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
		return (EXIT_FAILURE);
	if (histsave)
		while (histsave[++i])
			ft_putendl_fd(histsave[i], fd);
	return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

static char	*made_history(char *str)
{
	char		*ret;
	int			i;
	int			j;

	j = 0;
	i = 0;
	ret = NULL;
	if (str && str[1] && str[2])
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		while (str[++i] && str[i + 1])
		{
			if (i != 0 && str[i + 1])
				ret[j++] = str[i];
		}
		ret[j] = '\0';
	}
	return (ret);
}

static void	add_memory(char *news, char ***histsave)
{
	char	*s;
	char	tmp[ft_strlen(news) + 2];
	int		histfilesize;

	//s = ft_getenv("HISTSIZE", g_set);
//	histsize = s && ft_strisdigit(s) ? ft_atoi(s) : 500;
	//ft_strdel(&s);
	s = *histsave ? made_history((*histsave)[ft_tablen(*histsave) - 1]) : NULL;
	ft_strcpy(tmp, "[");
	ft_strncat(tmp, news, ft_strlen(news) - 1);
	if ((!*histsave || ft_strcmp(s, tmp + 1)) && HISTSIZE > 0)
	{
		ft_strdel(&s);
		histfilesize = *histsave ? ft_tablen(*histsave) + 1 : 1;
		while (--histfilesize >= HISTSIZE && histfilesize >= 0)
			ft_strdel_in_tab(histsave, 0);
		//s = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
		//add_to_set("HISTFILESIZE", s);
		//ft_strdel(&s);
		ft_malloc_cmd(histsave, strcat(tmp, "]"));
		//s = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
		//add_to_set("HISTFILESIZE", s);
	}
	ft_strdel(&s);
}

void		history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;

	if (version == -1)
	{
		path = ft_strdup(s);
		histsave = ft_tabdup(*history);
	}
	else if (version == 0 && histsave)
		*history = ft_tabdup(histsave);
	else if (version == 1 && news[1])
	{
		add_memory(news, &histsave);
	}
	else if (version == 2)
	{
		tmp = ft_strjoin(path, "/.101sh_history");
		save_to_file(histsave, tmp);
		ft_tabdel(&histsave);
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}


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

static void		cut_crochet_historic(char ***history)
{
	char	**tmp;
	char	*tmp_2;
	int		i;

	i = -1;
	tmp = NULL;
	if (*history)
	{
		while (*history && (*history)[++i])
			if ((*history)[i][0] == '[' &&
				(*history)[i][ft_strlen((*history)[i]) - 1] == ']')
			{
				tmp_2 = ft_strsub((*history)[i], 1,
						ft_strlen((*history)[i]) - 2);
				ft_malloc_cmd(&tmp, tmp_2);
				free(tmp_2);
			}
		ft_tabdel(history);
		if (tmp)
			*history = ft_tabdup(tmp);
		ft_tabdel(&tmp);
	}
}

static void		the_last_of_dowm(t_shell *sh)
{
	sh->hist = -2;
	ft_pushed_key_home_end(sh, FT_KEY_HOME);
	TERMCAP("cd");
	ft_strdel(&g_cmd);
	if (sh->tmp_line)
	{
		g_cmd = ft_strdup(sh->tmp_line);
		ft_strdel(&sh->tmp_line);
		ft_putstr(g_cmd);
	}
	g_cursor_pos = g_cmd ? ft_strlen(g_cmd) : 0;
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
		ft_strdel(&g_cmd);
		g_cmd = ft_strdup(history[sh->hist]);
		ft_putcmd(sh, ft_strlen(g_cmd));
	}
}

void			history_get(t_shell *sh, char key[])
{
	char		**history;

	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	cut_crochet_historic(&history);
	if (history && key[2] == 65 && sh->hist == -2 && g_cmd)
		sh->tmp_line = ft_strdup(g_cmd);
	if (history && sh->tmp_line)
		advanced_history(&history, sh->tmp_line);
	if (history)
	{
		if ((sh->hist + 1 < ft_tablen(history) && key[2] == 65) ||
			(sh->hist >= 0 && key[2] == 66) || (sh->hist == -2 && key[2] == 65))
			heart_of_hist_search(sh, history, key);
		if (key[2] == 66 && sh->hist == -1 && g_cmd)
			the_last_of_dowm(sh);
		ft_tabdel(&history);
	}
	else
		ft_strdel(&sh->tmp_line);
}
//
static int	ft_pushed_key_altup_altdown_check(t_shell *sh, char *key, int lr[2],
		int target)
{
	if (!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? !g_cursor_pos : lr[1] == -1)
	{
		TERMCAP("rc");
		return (1);
	}
	else
	{
		if (!ft_strncmp(FT_KEY_ALT_UP, key, 4))
		{
			if (lr[0] < target)
				target = lr[0];
			ft_pushed_left(sh);
		}
		else
			ft_pushed_right(sh);
		while (ft_recup_cursor_pos(sh, &lr[0], &lr[1]) != target &&
		(!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? g_cursor_pos :
		lr[1] != -1 && lr[1] != 0))
			!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? ft_pushed_left(sh) :
				ft_pushed_right(sh);
	}
	return (0);
}

int			ft_pushed_key_altup_altdown(t_shell *sh, char key[])
{
	int target;
	int cur_pos;
	int lr[2];

	ft_memset(lr, 0, sizeof(lr));
	cur_pos = g_cursor_pos;
	TERMCAP("sc");
	target = ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	while (!ft_strncmp(FT_KEY_ALT_UP, key, 4) ?
	g_cursor_pos && lr[1] != 0 : (lr[1] != -1 && lr[1] != 0))
	{
		!ft_strncmp(FT_KEY_ALT_UP, key, 4) ?
		ft_pushed_left(sh) : ft_pushed_right(sh);
		ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	}
	if (ft_pushed_key_altup_altdown_check(sh, key, lr, target))
		g_cursor_pos = cur_pos;
	return (0);
}

int			ft_pushed_key_altleft_altright(t_shell *sh, char key[])
{
	int i;

	i = g_cursor_pos;
	while (!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ? i > 0 : i <
			(int)ft_strlen(g_cmd))
	{
		if ((i == 0 || ft_isspace(g_cmd[i - 1])) && !ft_isspace(g_cmd[i]) &&
				ft_isprint(g_cmd[i]) && i != g_cursor_pos)
			break ;
		!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ? i-- : i++;
	}
	if (!((i == 0 || ft_isspace(g_cmd[i - 1])) && !ft_isspace(g_cmd[i]) &&
				ft_isprint(g_cmd[i]) && i != g_cursor_pos))
		return (0);
	while (g_cursor_pos != i)
		!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ?
		ft_pushed_left_right(sh, FT_KEY_LEFT) :
		ft_pushed_left_right(sh, FT_KEY_RIGHT);
	return (0);
}

int			ft_pushed_left_right(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	else if (!ft_strcmp(FT_KEY_LEFT, key))
		ft_pushed_left(sh);
	else if (!ft_strcmp(FT_KEY_RIGHT, key))
		ft_pushed_right(sh);
	return (0);
}

int			ft_pushed_up_down(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
	{
		//printf("EIF\n");
		//FLECHE DANS LA TABULATION
		return (ft_pushed_key_tab(sh, key));
	}
	else
	{
		//FLECHE DANS L'HISTORIC
		history_get(sh, key);
	}
	return (0);
}
