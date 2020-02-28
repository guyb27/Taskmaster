/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;

	ret = NULL;
	if (s1 && s2)
	{
		if (!(ret = malloc((ft_strlen((char*)s1) + ft_strlen((char*)s2)
							* sizeof(char)) + 1)))
			return (NULL);
		i = 0;
		while (*s1)
			ret[i++] = *s1++;
		while (*s2)
			ret[i++] = *s2++;
		ret[i] = '\0';
	}
	return (ret);
}
