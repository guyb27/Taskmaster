/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	void	ftpf_debug_flags(t_flags *flags)
**	{
**		printf("flags->zero_prefix: %d\n", flags->zero_prefix);
**		printf("flags->padding_left: %d\n", flags->padding_left);
**		printf("flags->show_sign: %d\n", flags->show_sign);
**		printf("flags->blank_sign: %d\n", flags->blank_sign);
**		printf("flags->sharp: %d\n", flags->sharp);
**		printf("flags->point: %d\n", flags->point);
**		printf("flags->width: %d\n", flags->width);
**		printf("flags->precision: %d\n", flags->precision);
**		printf("flags->length: %d\n", flags->length);
**		printf("flags->letter: %c\n", flags->letter);
**		printf("flags->flags_len: %d\n", flags->flags_len);
**	}
*/

void	ftpf_flags_init(t_flags *flags)
{
	flags->zero_prefix = 0;
	flags->padding_left = 0;
	flags->show_sign = 0;
	flags->blank_sign = 0;
	flags->sharp = 0;
	flags->point = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->length = 0;
	flags->letter = 0;
	flags->flags_len = 0;
	flags->arg_len = 0;
}

int		ftpf_flags_format(const char *s, t_flags *flags)
{
	if (*s == '-')
		flags->padding_left = 1;
	else if (*s == '0')
		flags->zero_prefix = 1;
	else if (*s == '+')
		flags->show_sign = 1;
	else if (*s == ' ')
		flags->blank_sign = 1;
	else if (*s == '#')
		flags->sharp = 1;
	else
		return (0);
	return (1);
}

int		ftpf_flags_width(const char *s, t_flags *flags)
{
	int		i;

	if (!ft_isdigit(s[0]))
		return (0);
	flags->width = 0;
	i = -1;
	while (ft_isdigit(s[++i]))
		flags->width = (flags->width * 10) + s[i] - '0';
	return (flags->width);
}

int		ftpf_flags_precision(const char *s, t_flags *flags)
{
	int		i;

	if (!ft_isdigit(s[0]))
		return (0);
	flags->precision = 0;
	i = -1;
	while (ft_isdigit(s[++i]))
		flags->precision = (flags->precision * 10) + s[i] - '0';
	return (!flags->precision ? 1 : flags->precision);
}

int		ftpf_flags_length(const char *s, t_flags *flags)
{
	int	old_length;

	old_length = flags->length;
	if (*s == 'h' && *(s + 1) == 'h')
		flags->length = 1;
	else if (*s == 'h')
		flags->length = 2;
	else if (*s == 'l' && *(s + 1) == 'l')
		flags->length = 4;
	else if (*s == 'l')
		flags->length = 3;
	else if (*s == 'j')
		flags->length = 5;
	else if (*s == 'z')
		flags->length = 6;
	else
		return (0);
	if ((int)flags->length < old_length)
		flags->length = old_length;
	return (1);
}
