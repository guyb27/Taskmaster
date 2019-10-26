/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 15:01:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static char	*tab_replace_tild(char *line)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (line && line[0] == '~' && (line[1] == '/' || !line[1]))
	{
		if ((tmp = ft_getenv("HOME", g_set)))
		{
			ret = line[1] && tmp ? ft_strjoin(tmp, line + 1) : ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else
			ret = ft_strdup(line);
	}
	else
		ret = ft_strdup(line);
	return (ret);
}

int			add_bin_tab(t_shell **sh, DIR *dir, char *path)
{
	struct dirent	*t_dir;
	char			*tmp;
	char			*line;
	int				len_file;
	char			*tmp2;

	line = (*sh)->t.word;
	while ((t_dir = readdir(dir)))
	{
		tmp2 = ft_strdup(t_dir->d_name);
		echap_char(&tmp2);
		len_file = (*sh)->t.is_file ? ft_strlen((*sh)->t.is_file) : 0;
		tmp = ft_stat(tmp2, path) == '2' ?
			ft_strjoin(tmp2, "/") : ft_strdup(tmp2);
		if ((line && 0 == ft_strncmp(line, tmp, ft_strlen(line))) ||
				(!line && tmp[0] != '.'))
		{
			ft_add_to_str(&(*sh)->t.is_file, ft_stat(tmp2, path), len_file);
			ft_malloc_cmd(&(*sh)->t.elem, tmp);
		}
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	ft_strdel(&line);
	return (0);
}

void		manage_first_tab(t_shell **sh, char key[])
{
	if ((*sh)->t.elem && (*sh)->t.elem[1])
	{
		(*sh)->tabu = 0;
		ft_init_select(sh);
		ft_select(sh, 0, key);
		(*sh)->tabu = 0;
	}
	else if ((*sh)->t.elem)
	{
		(*sh)->sel = malloc(sizeof(t_select));
		(*sh)->sel->ret = ft_strdup((*sh)->t.elem[0]);
		replace_line_after_tab(sh);
		free((*sh)->sel);
		ft_free_t_tab(&(*sh)->t);
		(*sh)->tabu = -1;
	}
	else
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar);
		ft_free_t_tab(&(*sh)->t);
		(*sh)->tabu = -1;
	}
}

void		first_tab(t_shell **sh, char key[])
{
	if (lexer_tab(sh) != -1)
	{
		printf("0LOL\n");
		if ((*sh)->t.nb_word == 1 || (*sh)->t.nb_word == 0)
		{
		printf("1LOL\n");
			search_bin_tab(sh);
		}
		else if ((*sh)->t.nb_word == -1)
		{
		printf("2LOL\n");
			//(*sh)->t.elem = search_var_tab((*sh)->t.word); OBSOLETE LOCAL VAR
		}
		else
		{
		printf("3LOL\n");
			search_in_rep_tab(sh);
		}
		manage_first_tab(sh, key);
	}
	else
	{

		printf("4LOL\n");
		ft_free_t_tab(&(*sh)->t);
	}
}

int			tabulator(t_shell **ed, int version, char key[])
{
	version != 0 ? place_cursor_before(*ed) : 0;
	if ((*ed)->tabu == -1 && version == 1)
		first_tab(ed, key);
	else if ((*ed)->tabu >= 0 && version == 1 && !(key[0] == 10 && key[1] == 0))
	{
		if ((*ed)->t.elem && (*ed)->t.elem[1])
			ft_select(ed, 1, key);
		ft_strdel(&(*ed)->t.word);
	}
	else if (version == 2)
	{
		if ((*ed)->sel->bp < (*ed)->sel->ws.ws_col)
			ft_print_params((*ed)->sel);
		ft_strdel(&(*ed)->t.word);
	}
	else if (version == 0 ||
			(version == 1 && key[0] == 10 && key[1] == 0 && (*ed)->tabu >= 0))
		end_tab_sequence(*ed);
	version != 0 ? place_cursor_after(*ed) : 0;
	return (0);
}
