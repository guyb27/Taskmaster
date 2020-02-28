/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_in_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:36 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:36 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strdel_in_tab(char ***tablo, int index)
{
	int			i;
	char		**tmp;

	i = 0;
	tmp = NULL;
	if (*tablo && (*tablo)[1])
	{
		while (i < index)
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
		if ((*tablo)[i + 1])
			while ((*tablo)[++i])
				if (ft_malloc_cmd(&tmp, (*tablo)[i]))
					return (1);
		ft_tabdel(&(*tablo));
		if (!(*tablo = ft_tabdup(tmp)))
		{
			ft_tabdel(&tmp);
			return (1);
		}
		ft_tabdel(&tmp);
	}
	else if (*tablo)
		ft_tabdel(&(*tablo));
	return (0);
}
