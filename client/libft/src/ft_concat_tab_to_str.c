/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_tab_to_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:33 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:33 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_concat_tab_to_str(char **tablo, char **str)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (tablo[++i])
		len += ft_strlen(tablo[i]);
	*str = (char*)malloc(sizeof(char) * (len + 1));
	i = -1;
	len = 0;
	while (tablo[++i])
	{
		j = 0;
		while (tablo[i][j])
			(*str)[len++] = tablo[i][j++];
	}
	(*str)[len] = '\0';
	return (0);
}
