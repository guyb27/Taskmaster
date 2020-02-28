/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:32 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:32 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_add_to_str(char **str, char c, int index)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(tmp = (char*)malloc(sizeof(char) *
		((*str ? ft_strlen(*str) : 0) + 2))))
		return (1);
	while (*str && (*str)[i] && i < index)
		tmp[j++] = (*str)[i++];
	tmp[j++] = c;
	while (*str && (*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = '\0';
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (0);
}
