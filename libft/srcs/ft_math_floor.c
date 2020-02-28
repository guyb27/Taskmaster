/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

double	ft_math_floor(double nb)
{
	int	int_nb;

	int_nb = nb;
	if (nb > 0)
		return (int_nb);
	if ((double)int_nb == nb)
		return (nb);
	return (int_nb - 1);
}
