/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:23 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:23 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	str_start;
	size_t	str_end;
	char	*ret;
	int		i;

	str_start = 0;
	str_end = 0;
	i = 0;
	ret = NULL;
	if (s)
	{
		while (s[i] && ft_isspace(s[i++]))
			str_start++;
		i = ft_strlen((char *)s) - 1;
		while (s[i] && ft_isspace(s[i--]))
			str_end++;
		if (ft_strlen((char *)s) <= (str_start + str_end))
			return (ft_strnew(0));
		ret = ft_strsub(s, str_start,
						(ft_strlen((char *)s) - (str_start + str_end)));
	}
	return (ret);
}
