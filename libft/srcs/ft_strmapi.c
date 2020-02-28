/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	ret = NULL;
	if (s)
	{
		if (!(ret = malloc((ft_strlen((char *)s) * sizeof(char)) + 1)))
			return (NULL);
		i = 0;
		while (*s)
		{
			ret[i] = f(i, *s++);
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
