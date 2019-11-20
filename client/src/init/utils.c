/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 06:42:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 09:49:35 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int					index_to_var(char *name, char **env)
{
	int				i;
	int				j;

	j = 0;
	i = -1;
	if (name && env)
	{
		while (env[++i])
		{
			j = 0;
			while (env[i][j] == name[j] && env[i][j] && name[j])
				j++;
			if (env[i][j] == '=' && j > 0)
				return (i);
		}
	}
	return (-1);
}

static char			*found_slash(int i[2], char *bin, char **tmp_1, char **tmp)
{
	char			*tmp_2;

	if (i[0] > 0 && bin[i[0] - 1] == '/')
	{
		while (i[0] > 0 && bin[i[0]] == '/')
			i[0] = i[0] - 1;
		i[0] = i[0] + 1;
	}
	if (!(i[0] == 0 || (i[0] == 1 && bin[0] == '.')))
	{
		if (bin[0] == '/' || bin[0] == '.')
		{
			while (bin[i[1]] == '.')
				i[1] = i[1] + 1;
			while (bin[i[1]] == '/')
				i[1] = i[1] + 1;
		}
		tmp_2 = ft_strsub(bin, i[1], i[0] - i[1]);
		*tmp_1 = ft_strjoin("/", tmp_2);
		ft_strdel(&tmp_2);
		tmp_2 = ft_strjoin(*tmp, *tmp_1);
		ft_strdel(tmp_1);
		return (tmp_2);
	}
	return (NULL);
}

char				*search_path_of_101sh(const char *bin)
{
	char			*tmp;
	char			*tmp_1;
	char			*tmp_2;
	char			buff[4096];
	int				i[2];

	i[1] = 0;
	tmp_1 = NULL;
	tmp = ft_strdup(getcwd(buff, sizeof(buff)));
	if (bin)
	{
		i[0] = ft_strlen(bin);
		while (i[0] >= 0)
		{
			if (bin[i[0]] == '/')
			{
				tmp_2 = found_slash(i, (char *)bin, &tmp_1, &tmp);
				tmp_2 ? ft_strdel(&tmp) : 0;
				return (tmp_2 ? tmp_2 : tmp);
			}
			!(bin[i[0]] == '/') ? i[0]-- : 0;
		}
	}
	return (tmp);
}

void				ft_handle_resize(int sig)
{
	int				tmp_cursor;
	t_shell			sh;

	(void)sig;
	ft_get_cols(&sh.ws);
	sh.prompt_len = g_cl.cmd ? ft_strlen(g_cl.cmd) : 0;
	tmp_cursor = g_cl.cursor_pos;
	TERMCAP("cl");
	ft_putstr(g_cl.prompt);
	g_cl.cursor_pos = 0;
	g_cl.cmd ? ft_reprint_cmd(&sh) : 0;
	g_cl.cursor_pos = g_cl.cmd ? ft_strlen(g_cl.cmd) : 0;
	while (tmp_cursor < g_cl.cursor_pos)
		ft_pushed_left(&sh);
}
