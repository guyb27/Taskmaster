/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:15 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (sign ? -res : res);
}
