/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:18 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:18 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
