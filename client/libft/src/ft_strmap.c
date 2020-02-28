/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:37 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:37 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	size_t	i;

	i = -1;
	if (s)
	{
		if (!(str = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[++i])
			str[i] = f(str[i]);
		return (str);
	}
	return (NULL);
}
