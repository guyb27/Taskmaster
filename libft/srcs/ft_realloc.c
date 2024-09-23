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

#ifdef __APPLE__
    #include <malloc/malloc.h>   // Pour macOS
#else
    #include <stdlib.h>           // Pour Linux et autres systèmes
#endif



void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	i;
	size_t	msize;

	if (!size || !ptr)
		return (NULL);
#ifdef __APPLE__
	msize = malloc_size(ptr);  // Utilisé uniquement sur macOS
#else
    // Vous pouvez gérer la taille allouée manuellement sur Linux ou faire une autre logique ici
    // Par exemple, passer la taille originale en paramètre de ft_realloc si nécessaire
    // msize = <size_originale que vous avez stockée ou passée>
	msize = 99999;
	
#endif
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
