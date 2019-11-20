/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 06:07:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 04:44:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

void	ft_free_t_tab(t_tab *t)
{
	ft_tabdel(&(*t).cmd);
	ft_tabdel(&(*t).elem);
	ft_strdel(&(*t).is_file);
	ft_strdel(&(*t).before);
	ft_strdel(&(*t).word);
	(*t).nb_word = 0;
	(*t).nb_char = 0;
}

int		ft_free_t_select(t_select **t)
{
	t_line		*tmp;

	if (!(*t))
		return (0);
	if (!(*t)->line)
	{
		free((*t));
		*t = NULL;
		return (0);
	}
	while ((*t)->line)
	{
		tmp = (*t)->line;
		(*t)->line = (*t)->line->next;
		if (tmp->elem)
			ft_strdel(&tmp->elem);
		free(tmp);
		tmp = NULL;
	}
	free(*(t));
	*t = NULL;
	return (0);
}
