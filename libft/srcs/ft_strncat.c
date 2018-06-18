/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:22 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:22 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	while (dest[i])
		i++;
	j = -1;
	while (src[++j] && j < n)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}
