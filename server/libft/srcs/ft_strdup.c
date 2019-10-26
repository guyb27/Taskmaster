/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:20 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:20 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char *ret;

	ret = 0;
	if (!(ret = malloc((ft_strlen(src) + 1) * sizeof(char))))
		return (ret);
	ft_strcpy(ret, src);
	return (ret);
}
