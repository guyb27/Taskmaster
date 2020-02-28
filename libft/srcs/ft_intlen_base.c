/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:15 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_intlen_base(long long n, int base_len)
{
	long long i;

	if (base_len < 2)
		return (1);
	i = n < 0 && base_len == 10;
	while (n /= base_len)
		i++;
	return (i + 1);
}
