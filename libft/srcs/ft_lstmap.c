/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:16 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:16 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
