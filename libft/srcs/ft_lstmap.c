/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first_elem;
	t_list	*new_elem;
	t_list	*prev_elem;

	first_elem = NULL;
	new_elem = NULL;
	prev_elem = NULL;
	if (f)
	{
		while (lst)
		{
			if (!(new_elem = ft_lstnew(lst->content, lst->content_size)))
				return (NULL);
			new_elem = f(new_elem);
			if (!first_elem)
				first_elem = new_elem;
			if (prev_elem)
				prev_elem->next = new_elem;
			prev_elem = new_elem;
			lst = lst->next;
		}
	}
	return (first_elem);
}
