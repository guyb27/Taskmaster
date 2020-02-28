/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:38 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:38 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_wordcount(const char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			while (s[i] != c && s[i])
			{
				if (s[i + 1] == c || !(s[i + 1]))
					count++;
				i++;
			}
		}
	}
	return (count);
}
