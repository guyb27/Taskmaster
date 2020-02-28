/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_isprime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_isprime(int nb)
{
	int i;
	int max_to_check;

	if (nb > FT_INT_MAX || nb < 2)
		return (0);
	else if (nb == 2)
		return (1);
	max_to_check = nb / 2;
	i = 3;
	while (i <= max_to_check)
	{
		if (!(nb % i))
			return (0);
		i += 2;
	}
	return (nb % 2 == 0 ? 0 : 1);
}
