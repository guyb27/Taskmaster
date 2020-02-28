/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:33 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:33 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*after;
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		after = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = after;
	}
	*alst = (NULL);
}
