/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:41 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:54:41 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_select.h"

void		ft_greater(t_line **search, t_line **after)
{
	(*search)->next = *after;
	(*after)->prev = *search;
	(*after)->next = NULL;
}

void		ft_smaller(t_line **now, t_line **tmp, t_line **begin)
{
	t_line	*tmp2;

	if ((*now)->prev)
	{
		tmp2 = (*now)->prev;
		(*now)->prev = *tmp;
		tmp2->next = *tmp;
		(*tmp)->prev = tmp2;
		(*tmp)->next = *now;
	}
	else
	{
		(*now)->prev = *tmp;
		(*tmp)->prev = NULL;
		(*tmp)->next = *now;
		*begin = *tmp;
	}
}

void		ft_first_sort(t_line **line, char *av)
{
	t_line		*search;
	t_line		*after;

	after = malloc(sizeof(t_line));
	after->x_char_pos = 0;
	after->x_param_pos = 0;
	after->y_pos = 0;
	after->ds = 0;
	after->elem = ft_strdup(av);
	search = (*line);
	while (search->next && ft_strcmp(search->elem, av) < 0)
		search = search->next;
	ft_strcmp(search->elem, av) < 0 ? ft_greater(&search, &after) :
	ft_smaller(&search, &after, &(*line));
}
