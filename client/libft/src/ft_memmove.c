/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*srce;
	char		*dest;

	srce = src;
	dest = dst;
	if (srce <= dest)
	{
		srce += len - 1;
		dest += len - 1;
		while (len--)
			*dest-- = *srce--;
	}
	else
		ft_memcpy(dest, srce, len);
	return (dst);
}
