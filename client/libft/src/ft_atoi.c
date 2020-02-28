/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:32 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:32 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int				ft_atoi(const char *nptr)
{
	int			i;
	int			nb;
	char		neg;

	i = 0;
	nb = 0;
	neg = '\0';
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		neg = nptr[i];
	i += neg ? 1 : 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	return (neg == '-' ? nb * (-1) : nb);
}
