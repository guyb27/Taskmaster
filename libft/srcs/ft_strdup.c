/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:19 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:19 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
