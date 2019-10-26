/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:23 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:23 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_str_split_dup(char *str, char c)
{
	char	*ret;
	int		i;

	ret = NULL;
	if (!(ret = malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	ft_strncpy(ret, str, i);
	ret[i] = '\0';
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	size = 0;
	i = -1;
	while (s[++i])
		if ((!i || s[i - 1] == c) && s[i] != c)
			size++;
	ret = NULL;
	if (!(ret = malloc((size + 1) * sizeof(char *))))
		return (NULL);
	ret[size] = NULL;
	i = -1;
	j = -1;
	while (s[++i])
		if ((!i || s[i - 1] == c) && s[i] != c)
			if (!(ret[++j] = ft_str_split_dup((char *)s + i, c)))
				return (NULL);
	return (ret);
}
