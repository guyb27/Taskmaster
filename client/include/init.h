/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:41:57 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 08:23:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "heart.h"

int			init_shell(int ac, const char **av);
char		*search_path_of_101sh(const char *bin);
int			index_to_var(char *name, char **env);
void		ft_handle_resize(int sig);

#endif
