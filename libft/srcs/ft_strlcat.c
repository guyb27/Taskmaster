/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:21 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:21 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t dst_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	if (!size)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	while (src[j] && i < size - 1)
		dst[i++] = src[j++];
	if (size && size >= dst_len)
		dst[i] = '\0';
	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + dst_len);
}
