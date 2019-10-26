/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr_int.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:23 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:23 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
