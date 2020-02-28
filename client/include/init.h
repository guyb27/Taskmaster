/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:00:23 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:00:23 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "heart.h"

int			init_shell(const char **av);
char		*search_path_of_101sh(const char *bin);
int			index_to_var(char *name, char **env);
void		ft_handle_resize(int sig);

#endif
