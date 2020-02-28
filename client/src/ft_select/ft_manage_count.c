/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:41 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:54:41 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int		ft_params_by_line(t_select *t)
{
	int		ret;
	int		i;
	int		big_param;
	int		nb_char;

	ret = 0;
	i = 0;
	nb_char = 0;
	big_param = ft_search_big_param(t->line);
	while (i != -1 && t->line)
	{
		if (nb_char == 0 && nb_char + big_param <= t->ws.ws_col)
			ret++;
		else if (nb_char + big_param + 1 <= t->ws.ws_col)
			ret++;
		else
			i = -1;
		nb_char += ret == 0 ? big_param : big_param + 1;
	}
	return (ret);
}

int		ft_char_by_line(t_select **sel)
{
	int		res;
	int		nb_arg;

	nb_arg = ft_count_params((*sel)->line);
	if (nb_arg == 1)
		res = ft_search_big_param((*sel)->line);
	else
		res = ft_search_big_param((*sel)->line) * nb_arg + 1 * nb_arg - 1;
	return (res);
}

int		ft_count_line(t_select *t)
{
	if (ft_params_by_line(t))
	{
		return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
				ft_count_params(t->line) / ft_params_by_line(t) :
				ft_count_params(t->line) / ft_params_by_line(t) + 1);
	}
	return (0);
}

int		ft_count_params(t_line *line)
{
	int		i;

	i = 0;
	while (line)
	{
		line = line->next;
		i++;
	}
	return (i);
}
