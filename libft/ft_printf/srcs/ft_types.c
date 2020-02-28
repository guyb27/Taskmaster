/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ftpf_get_signed_from_len(t_flags *flags)
{
	intmax_t	nb;

	if (flags->length == none)
		nb = (int)flags->arg;
	else if (flags->length == hh)
		nb = (char)flags->arg;
	else if (flags->length == h)
		nb = (short int)flags->arg;
	else if (flags->length == ll)
		nb = (long long int)flags->arg;
	else if (flags->length == l)
		nb = (long int)flags->arg;
	else if (flags->length == j)
		nb = (intmax_t)flags->arg;
	else if (flags->length == z)
		nb = (size_t)flags->arg;
	else
		nb = flags->arg;
	return (nb);
}

intmax_t	ftpf_get_u_from_len(t_flags *flags)
{
	intmax_t	nb;

	if (flags->length == none)
		nb = (unsigned int)flags->arg;
	else if (flags->length == hh)
		nb = (unsigned char)flags->arg;
	else if (flags->length == h)
		nb = (unsigned short int)flags->arg;
	else if (flags->length == ll)
		nb = (unsigned long long int)flags->arg;
	else if (flags->length == l)
		nb = (unsigned long int)flags->arg;
	else if (flags->length == j)
		nb = (uintmax_t)flags->arg;
	else if (flags->length == z)
		nb = (size_t)flags->arg;
	else
		nb = flags->arg;
	return (nb);
}
