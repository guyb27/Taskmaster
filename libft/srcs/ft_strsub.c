/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:23 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:23 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	ret = NULL;
	if (s)
	{
		s += start;
		if (!(ret = malloc((len * sizeof(char)) + 1)))
			return (NULL);
		i = 0;
		while (*s && len--)
			ret[i++] = *s++;
		ret[i] = '\0';
	}
	return (ret);
}
