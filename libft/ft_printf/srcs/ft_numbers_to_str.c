/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 04:21:40 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ftpf_l_itoab(intmax_t n, char *base)
{
	char	*ret;
	int		len;
	int		baselen;

	if (n == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	baselen = ft_strlen(base);
	len = ft_intlen_base(n, baselen) + 1;
	if (!(ret = malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (n < 0 && baselen == 10)
	{
		ret[0] = '-';
		n = -n;
	}
	if (!n)
		*ret = base[0];
	ret[len - 1] = '\0';
	while (n)
	{
		len--;
		ret[len - 1] = base[n % baselen];
		n /= baselen;
	}
	return (ret);
}

char		*ftpf_ul_itoab(uintmax_t n, char *base)
{
	char	*ret;
	int		len;
	int		baselen;

	baselen = ft_strlen(base);
	len = ft_u_intlen_base(n, baselen) + 1;
	if (!(ret = malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (!n)
		*ret = base[0];
	ret[len - 1] = '\0';
	while (n)
	{
		len--;
		ret[len - 1] = base[n % baselen];
		n /= baselen;
	}
	return (ret);
}

static char	*ftpf_dtoa_inner(double n, intmax_t int_part, intmax_t dec_part,
																		int len)
{
	char	*ret;

	if (!(ret = malloc((len + 2) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		ret[0] = '-';
		n = -n;
		len++;
	}
	if (!int_part && !dec_part)
		*ret = '0';
	ret[++len] = '\0';
	while (dec_part && len--)
	{
		ret[len] = dec_part % 10 + '0';
		dec_part /= 10;
	}
	ret[--len] = '.';
	while (int_part && len--)
	{
		ret[len] = int_part % 10 + '0';
		int_part /= 10;
	}
	return (ret);
}

char		*ftpf_dtoa(double n, unsigned int precision)
{
	intmax_t		int_part;
	intmax_t		dec_part;
	intmax_t		tmp;
	int				len;
	unsigned int	prec;

	prec = precision ? precision : 6;
	int_part = (intmax_t)ft_abs(n);
	dec_part = (float)(ft_abs(n) - (float)int_part) * ft_math_pow(10, prec);
	if (dec_part < 0)
		dec_part = (ft_abs(n) - (long)ft_abs(n)) * ft_math_pow(10, prec);
	tmp = int_part;
	len = 0;
	while (tmp && ++len)
		tmp /= 10;
	tmp = dec_part;
	while (tmp && ++len)
		tmp /= 10;
	return (ftpf_dtoa_inner(n, int_part, dec_part, len));
}
