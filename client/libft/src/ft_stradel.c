/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:35 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:35 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_stradel(char ***array)
{
	int i;

	i = -1;
	while ((*array)[++i])
		ft_strdel(&(*array)[i]);
	ft_strdel(&(*array)[i]);
	free(*array);
}
