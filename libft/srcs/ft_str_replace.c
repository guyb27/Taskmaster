/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Replace a word in a string and add underline style to it
*/

char	*ft_str_replace(char *haystack, char *needle, char *new_word)
{
	int		size_diff;
	char	*needle_pos;
	char	*ret;
	int		str_size;

	ret = NULL;
	needle_pos = NULL;
	needle_pos = ft_strstr(haystack, needle);
	size_diff = ft_abs(ft_strlen(new_word) - ft_strlen(needle));
	str_size = ft_strlen(haystack) + size_diff + (sizeof(BDGREY) * 2);
	if (!(ret = (char *)ft_memalloc(str_size + 1)))
		return (NULL);
	ft_strncat(ret, haystack,
			(ft_abs(ft_strlen(haystack) - ft_strlen(needle_pos))));
	ft_strcat(ret, KUNDER);
	ft_strcat(ret, new_word);
	ft_strcat(ret, KRESUNDER);
	ft_strcat(ret, needle_pos + ft_strlen(needle));
	ret[str_size] = '\0';
	return (ret);
}
