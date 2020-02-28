/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_char_in_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:33 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:33 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_insert_char_in_str(char **str, char c, int at)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(*str))
		return (1);
	if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 2))))
		return (1);
	while ((*str)[i])
	{
		if (i == at && i == j)
			ret[j] = c;
		else
		{
			ret[j] = (*str)[i];
			i++;
		}
		j++;
	}
	ret[j] = '\0';
	ft_strdel(&(*str));
	return (0);
}
