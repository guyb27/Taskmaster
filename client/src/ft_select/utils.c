/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:42 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:54:42 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
