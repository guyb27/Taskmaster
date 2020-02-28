/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:35 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:35 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

int		ft_reverse_tab(char ***tablo)
{
	int		i;
	int		j;
	char	**tmp;

	if (*tablo)
	{
		i = ft_tablen(*tablo) - 1;
		j = 0;
		if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
			return (1);
		while (i >= 0)
			tmp[j++] = ft_strdup((*tablo)[i--]);
		tmp[j] = NULL;
		ft_tabdel(tablo);
		*tablo = ft_tabdup(tmp);
		ft_tabdel(&tmp);
	}
	return (0);
}
