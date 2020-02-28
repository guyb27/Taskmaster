/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void			*ft_shared_malloc(int size)
{
	void *var;

	var = mmap(NULL, size,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	return (var);
}

size_t			ft_tablen(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

int				ft_tabdel(char ***tab)
{
	int		i;

	i = -1;
	if (*tab)
	{
		while ((*tab)[++i])
			ft_strdel(&(*tab)[i]);
		free(*tab);
		*tab = NULL;
	}
	return (0);
}

char			**ft_tabdup(char **tab)
{
	int		i;
	char	**ret;

	i = -1;
	ret = NULL;
	if (!tab)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = NULL;
	return (ret);
}
