/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:17 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:17 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putnbr_hex(int octet, int rem)
{
	char base[17];

	ft_strcpy(base, "0123456789abcdef");
	if (rem > 1)
		ft_putnbr_hex(octet >> 4, rem - 1);
	write(1, base + (octet % 16), 1);
}

static void		ft_print_mem_hex(void *addr, unsigned int size, unsigned int a)
{
	unsigned int b;

	b = -1;
	while (++b < 16)
	{
		if ((a + b) < size)
			ft_putnbr_hex(*((unsigned char*)addr + a + b), 2);
		else
			ft_putstr("  ");
		if (b % 2)
			ft_putchar(' ');
	}
}

static void		ft_print_mem_str(void *addr, unsigned int size, unsigned int a)
{
	unsigned int b;

	b = -1;
	while (++b < 16 && (a + b) < size)
		if (ft_isprint(*((char*)addr + a + b)))
			ft_putchar(*((char*)addr + a + b));
		else
			ft_putchar('.');
}

void			*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int a;

	a = 0;
	while (a < size)
	{
		ft_putnbr_hex(*(int*)addr + a, 8);
		ft_putstr(": ");
		ft_print_mem_hex(addr, size, a);
		ft_putchar(' ');
		ft_print_mem_str(addr, size, a);
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}
