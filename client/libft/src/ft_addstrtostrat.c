/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstrtostrat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:32 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:32 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_addstrtostrat(char **str, char *to_add, int at)
{
	int		i[2];
	char	*tmp;
	int		add;

	add = 0;
	i[1] = 0;
	if (*str && to_add && at < (int)ft_strlen(*str) && at >= 0)
	{
		i[0] = ft_strlen(*str) + ft_strlen(to_add);
		if (!(tmp = (char*)malloc(sizeof(char) * (i[0] + 1))))
			return (1);
		i[0] = 0;
		while ((*str)[i[0]])
		{
			if (i[0] == at)
				while (to_add[i[1]])
					tmp[add++] = to_add[i[1]++];
			tmp[add++] = (*str)[i[0]++];
		}
		tmp[add] = '\0';
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (0);
}
