/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:33:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 02:24:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				init_env(const char *path)
{
	extern char	**environ;
	char		*s;

	if (!(s = ft_envset_value((const char **)environ, "TERM")))
		if (!(s = ft_strdup("xterm-256color")))
			return (EXIT_FAILURE);
	if (tgetent(NULL, s) == ERR)
		return (EXIT_FAILURE);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
