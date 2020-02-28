/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc/malloc.h>

void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	i;
	size_t	msize;

	if (!size || !ptr)
		return (NULL);
	msize = malloc_size(ptr);
	tmp = malloc(sizeof(char) * (size + 1));
	i = -1;
	while (++i < size && i < msize)
		tmp[i] = ((char*)ptr)[i];
	free(ptr);
	ptr = malloc(size);
	i = -1;
	while (++i < size && i < msize)
		((char*)ptr)[i] = (tmp)[i];
	free(tmp);
	return (ptr);
}
