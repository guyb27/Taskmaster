/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:22 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:22 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = ft_strlen((char *)s);
	if (!c)
		return ((char *)s + i);
	while (i-- >= 0)
		if (s[i] == (char)c)
			return ((char *)s + i);
	return (c == '\0' ? (char *)s + i : NULL);
}
