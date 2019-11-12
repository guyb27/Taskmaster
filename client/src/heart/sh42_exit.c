/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42_exit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 01:49:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		exit_shell(void)
{
//	if (g_env)
//		ft_tabdel(&g_env);
	ft_strdel(&g_cmd);
	history_save((char ***)NULL, (char *)NULL, 2, (char *)NULL);
	get_next_line(-101, NULL);
}
