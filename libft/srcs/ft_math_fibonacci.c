/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_fibonacci.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_math_fibonacci(int index)
{
	if (!index)
		return (0);
	else if (index < 0)
		return (-1);
	else if (index > 1)
		return (ft_math_fibonacci(index - 1) + ft_math_fibonacci(index - 2));
	else
		return (1);
}
