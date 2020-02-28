/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;
	t_list	*element;
	t_list	*tmp;

	if (!(element = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	element = f(lst);
	first = element;
	tmp = lst->next;
	while (tmp)
	{
		if (!(new = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		new = f(tmp);
		element->next = new;
		element = element->next;
		tmp = tmp->next;
		new = NULL;
	}
	return (first);
}
