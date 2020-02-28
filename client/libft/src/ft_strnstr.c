/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:37 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:37 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + f] == needle[f] && i + f < len)
		{
			f++;
			if (needle[f] == '\0')
			{
				while (i--)
					haystack++;
				return ((char *)haystack);
			}
		}
		f = 0;
		i++;
	}
	return (NULL);
}
