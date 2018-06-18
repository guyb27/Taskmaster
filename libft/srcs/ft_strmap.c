/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:21 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:21 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	int		i;

	ret = NULL;
	if (s)
	{
		if (!(ret = malloc((ft_strlen((char *)s) * sizeof(char)) + 1)))
			return (NULL);
		i = 0;
		while (*s)
			ret[i++] = f(*s++);
		ret[i++] = '\0';
	}
	return (ret);
}
