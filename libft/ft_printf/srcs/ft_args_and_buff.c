/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_and_buff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ftpf_concat(t_flags *flags, const char *str, size_t size)
{
	if (!(*flags->buff = realloc(*flags->buff,
					(g_bufflen + size + 3) * sizeof(char))))
		return (0);
	ft_memcpy(*flags->buff + g_bufflen, str, size);
	g_bufflen += size;
	return (1);
}

static int	ftpf_concat_arg(t_flags *flags)
{
	if (!flags->arg && flags->padding_left && flags->width &&
			flags->letter == 'c')
	{
		g_bufflen++;
		flags->arg_len--;
	}
	if (flags->letter == 'n')
		*((int*)flags->arg) = g_bufflen;
	if (!(ftpf_concat(flags, flags->output, flags->arg_len)))
	{
		free(flags->output);
		return (0);
	}
	free(flags->output);
	return (1);
}

int			ftpf_concat_buff(const char *format, t_flags *flags, int i, int j)
{
	if (i - j > 0)
	{
		if (ft_strchr(format + j, '{'))
		{
			if (!(ftpf_memcpy_modifiers((char*)format + j, flags, i - j)))
				return (-1);
		}
		else if (!(ftpf_concat(flags, format + j, i - j)))
			return (-1);
	}
	if (!format[i] || (int)ft_strlen(format + i) < flags->flags_len)
		return (i - j > 0 ? i - j : 0);
	if (!(ftpf_concat_arg(flags)))
		return (-1);
	return (i - j > 0 ? i - j : 0);
}

int			ftpf_process_arg(const char *format, t_flags *flags, va_list args)
{
	ftpf_parse_flags(format, flags, args);
	if ((flags->arg_len = ftpf_exec_args_func(flags)) < 0)
	{
		free(flags->output);
		flags->arg_len = 0;
		return (-1);
	}
	return (flags->arg_len);
}
