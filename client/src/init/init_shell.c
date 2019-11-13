/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:58:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 04:08:35 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
/*
static int	add_multiline(char **ret, char *news, char ***get_hist)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\n", news);
	tmp2 = ft_strjoin(*ret, tmp);
	ft_strdel(ret);
	*ret = ft_strdup(tmp2);
	if (news && ft_strlen(news) > 0 && news[ft_strlen(news) - 1] == ']')
	{
		ft_malloc_cmd(get_hist, *ret);
		ft_strdel(ret);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (0);
}

static int	add_hist_to_memory(char **tmp, char *path)
{
	char			**get_hist;
	int				i;
	char			*str;

	i = -1;
	str = NULL;
	get_hist = NULL;
	if (tmp)
		while (tmp[++i])
		{
			if (!str && tmp[i][0] == '[')
			{
				if (tmp[i][ft_strlen(tmp[i]) - 1] == ']')
					ft_malloc_cmd(&get_hist, tmp[i]);
				else
					str = ft_strdup(tmp[i]);
			}
			else if (str)
				add_multiline(&str, tmp[i], &get_hist);
		}
	ft_strdel(&str);
	history_save(&get_hist, NULL, -1, path);
	ft_tabdel(&get_hist);
	return (0);
}
*/
static int	init_builtins_history_read(int fd, int *i, char *path)
{
	char	*str;
	char	**tmp;

	str = NULL;
	tmp = NULL;
	while (get_next_line(fd, &str))
	{
		if (ft_malloc_cmd(&tmp, str))
			return (EXIT_FAILURE);
		(*i)++;
		ft_strdel(&str);
	}
	/*add_hist_to_memory(tmp, path);*/
	history_save(&tmp, NULL, -1, path);
	ft_tabdel(&tmp);
	return (EXIT_SUCCESS);
}

static int	init_history(const char *path)
{
	char	*str;
	int		fd;
	int		i;

	str = NULL;
	fd = -1;
	i = 0;
	if (!(str = ft_strjoin(path, HISTFILE)))
		return (EXIT_FAILURE);
	if ((fd = open(str, O_RDONLY)) == -1)
		return (EXIT_FAILURE + ft_strdel(&str));
	ft_strdel(&str);
	init_builtins_history_read(fd, &i, (char *)path);
	return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

char		*ft_envset_value(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(ft_strchr(envset[i], '=') + 1);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}

int			ft_init_term(int ac, const char **av)
{
	char		*path;
	char		*str;
	extern char	**environ;

	if (!(path = search_path_of_101sh(av[0])))
		return (EXIT_FAILURE);
	if ((access((str = ft_strjoin(path, "/.101sh_history")), F_OK)) == -1)
		creat(str, 0644);
	ft_strdel(&str);
	if (!(str = ft_envset_value((const char **)environ, "TERM")))
		if (!(str = ft_strdup("xterm-256color")))
			return (EXIT_FAILURE);
	if (tgetent(NULL, str) == ERR)
		return (EXIT_FAILURE);
	ft_strdel(&str);
	if (init_history((const char *)path))
	{
		ft_strdel(&path);
		return (EXIT_FAILURE);
	}
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}

int			init_shell(int ac, const char **av)
{
	pid_t shell_pgid;
	pid_t shell_pid;

	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		signal(SIGINT, ft_handle_sigint);
		signal(SIGWINCH, ft_handle_resize);
		shell_pid = getpid();
		tcsetpgrp(STDIN_FILENO, shell_pid);
		ft_init_term(ac, av);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
