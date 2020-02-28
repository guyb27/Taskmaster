/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:37 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:37 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		**ft_strsplit(const char *s, char c)
{
	char	**tab;
	size_t	w;
	size_t	i;
	int		v;

	i = 0;
	if (!(s))
		return (NULL);
	w = ft_wordcount(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	v = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			tab[v++] = ft_strsub(s, ((int)i), ft_wordlen(s, c, i));
			i += ft_wordlen(s, c, i);
		}
	}
	tab[v] = (NULL);
	return (tab);
}
