/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*element;

	if (!(element = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		element->content = (NULL);
		element->content_size = 0;
	}
	else
	{
		if (!(element->content = (void *)malloc(sizeof(void) * content_size)))
			return (NULL);
		ft_memmove(element->content, (void *)content, content_size);
		element->content_size = content_size;
	}
	element->next = (NULL);
	return (element);
}
