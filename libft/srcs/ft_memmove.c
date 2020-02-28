/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:17 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:17 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if ((char *)dst < (char *)src)
		ft_memcpy(dst, src, n);
	else
		while (n--)
			((char *)dst)[n] = ((char *)src)[n];
	return (dst);
}
