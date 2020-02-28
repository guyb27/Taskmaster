/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:36 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:36 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup_free(char *s1, char *to_free)
{
	int		i;
	char	*dest;

	i = -1;
	dest = NULL;
	if (!s1)
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	free(to_free);
	return (dest);
}
