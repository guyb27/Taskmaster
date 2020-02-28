/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strstr_int(const char *haystack, const char *needle)
{
	size_t	needle_len;

	if (!*needle)
		return (0);
	needle_len = ft_strlen((char *)needle);
	while (*haystack)
		if (!ft_memcmp(haystack++, needle, needle_len))
			return (1);
	return (0);
}
