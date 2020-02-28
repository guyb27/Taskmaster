/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_nbr_hex(int octet, int rem, char *buffer)
{
	char *base;

	base = "0123456789abcdef";
	if (rem > 1)
		ft_get_nbr_hex(octet >> 4, rem - 1, buffer);
	buffer[rem - 1] = base[octet % 16];
}

int			ftpf_handle_str_non_printable(t_flags *flags)
{
	int		i;
	char	hex[2];
	char	*str;

	str = (char*)flags->arg;
	flags->output = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (*str)
		if (ft_isprint(*str))
			(flags->output)[i++] = *str++;
		else
		{
			(flags->output)[i++] = '\\';
			ft_get_nbr_hex(*str++, 2, hex);
			(flags->output)[i++] = hex[0];
			(flags->output)[i++] = hex[1];
		}
	(flags->output)[i] = '\0';
	return (1);
}

int			ftpf_patch_colors(char *format, char *modifier, t_flags *flags)
{
	char	*color_code;
	int		mod_dist;
	int		len;

	mod_dist = modifier - format;
	color_code = NULL;
	if (!ft_strncmp(modifier, "{red}", (len = 5)))
		color_code = "\e[31m";
	else if (!ft_strncmp(modifier, "{green}", (len = 7)))
		color_code = "\e[32m";
	else if (!ft_strncmp(modifier, "{yellow}", (len = 8)))
		color_code = "\e[33m";
	else if (!ft_strncmp(modifier, "{blue}", (len = 6)))
		color_code = "\e[94m";
	else if (!ft_strncmp(modifier, "{purple}", (len = 8)))
		color_code = "\e[35m";
	else if (!ft_strncmp(modifier, "{cyan}", (len = 6)))
		color_code = "\e[96m";
	else if (!ft_strncmp(modifier, "{eoc}", (len = 5)))
		color_code = "\e[0m";
	if (color_code)
		if (!ftpf_concat(flags, color_code, ft_strlen(color_code)))
			return (-1);
	return (color_code ? len : 0);
}

int			ftpf_memcpy_modifiers(char *format, t_flags *flags, int size)
{
	char	*tmp;
	char	*modifier;
	int		ret;

	tmp = format;
	modifier = NULL;
	while ((modifier = ft_strchr(format, '{')) != NULL)
	{
		if (modifier - tmp >= size)
			break ;
		ftpf_concat(flags, format, modifier - format);
		if ((ret = ftpf_patch_colors(format, modifier, flags)) < 0)
			return (-1);
		format = modifier + ret;
		if (format == modifier)
			break ;
	}
	if (size - (format - tmp) > 0)
		ftpf_concat(flags, format, size - (format - tmp));
	return (1);
}
