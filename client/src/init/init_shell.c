/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:58:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 03:02:51 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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

int			ft_init_vars(int ac, const char **av)
{
	char	*path;
	char		*term_var;
	extern char	**environ;

	if (!(path = search_path_of_101sh(av[0])))
		return (EXIT_FAILURE);
	if (init_files(path))
	{
		ft_strdel(&path);
		return (EXIT_FAILURE);
	}
	if (!(term_var = ft_envset_value((const char **)environ, "TERM")))
		if (!(term_var = ft_strdup("xterm-256color")))
			return (EXIT_FAILURE);
	if (tgetent(NULL, term_var) == ERR)
		return (EXIT_FAILURE);
	ft_strdel(&term_var);
	if (init_builtins((const char *)path))
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

	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		signal(SIGINT, ft_handle_sigint);
		signal(SIGWINCH, ft_handle_resize);
		shell_pgid = getpid();
		tcsetpgrp(STDIN_FILENO, shell_pgid);
		ft_init_vars(ac, av);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
