/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_flags.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/19 18:00:52 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 18:23:40 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_parse_width(const char *format, t_flags *flags, va_list args)
{
	int	ret;

	ret = 0;
	if (ftpf_flags_width(format, flags))
		ret += ft_intlen(flags->width);
	if (*(format + ret) == '*')
	{
		flags->width = va_arg(args, int);
		if ((int)flags->width < 0)
		{
			flags->width = -flags->width;
			flags->padding_left = 1;
		}
		ret++;
	}
	if (ftpf_flags_width(format + ret, flags))
		ret += ft_intlen(flags->width);
	return (ret);
}

int		ftpf_parse_precision(const char *format, t_flags *flags, va_list args)
{
	int	ret;

	ret = 0;
	while (*(format + ret) == '.')
	{
		flags->point = 1;
		flags->precision = 0;
		if (ftpf_flags_precision(format + ret + 1, flags))
			ret += ft_intlen(flags->precision);
		ret++;
	}
	if (*(format + ret) == '*')
	{
		flags->precision = va_arg(args, int);
		if ((int)flags->precision < 0)
		{
			flags->point = 0;
			flags->precision = 0;
		}
		ret++;
	}
	return (ret);
}

void	ftpf_parse_flags(const char *format, t_flags *flags, va_list args)
{
	const char	*tmp;

	tmp = format - 1;
	ftpf_flags_init(flags);
	while (ftpf_flags_format(format, flags))
		format++;
	format += ftpf_parse_width(format, flags, args);
	format += ftpf_parse_precision(format, flags, args);
	while (ftpf_flags_length(format, flags))
		format += flags->length == 1 || flags->length == 4 ? 2 : 1;
	while (ftpf_flags_format(format, flags))
		format++;
	flags->letter = *format;
	if (ft_strchr("sSpdDioOuUxXcCbr", *format) && *format != '%')
		flags->arg = va_arg(args, intmax_t);
	else if (ft_strchr("fF", *format))
		flags->float_arg = va_arg(args, double);
	else if (*format == 'n')
		flags->arg = (intmax_t)va_arg(args, int*);
	flags->flags_len = format - tmp + 1;
}

int		ftpf_get_str_arg(t_flags *flags)
{
	if (flags->letter == 'c')
		return (ftpf_handle_char(flags));
	else if (flags->letter == 's')
		return (ftpf_handle_str(flags));
	else if (ft_strchr("diuxXofb", flags->letter) && flags->letter)
		return (ftpf_handle_numbers(flags));
	else if (flags->letter == '%')
		flags->output = ft_strdup("%");
	else if (flags->letter == 'p')
		return (ftpf_handle_pointer(flags));
	else if (flags->letter == 'r')
		return (ftpf_handle_str_non_printable(flags));
	else if (flags->letter == 'n')
		flags->output = ft_strdup("");
	else
	{
		flags->output = ft_memalloc(2);
		(flags->output)[0] = flags->letter;
	}
	return (1);
}

int		ftpf_exec_args_func(t_flags *flags)
{
	int		output_len;
	int		ret;

	ftpf_patch_upper_letter(flags);
	ret = ftpf_get_str_arg(flags);
	if (flags->width)
		ftpf_apply_width(flags);
	if (flags->letter == 'd' || flags->letter == 'i')
		ftpf_apply_sign(flags);
	if (flags->sharp)
	{
		if (ft_tolower(flags->letter) == 'x')
			ftpf_apply_sharp_hex(flags);
		else if (flags->letter == 'o')
			ftpf_apply_sharp_octal(flags);
	}
	ftpf_patch_sign_pos(flags);
	output_len = ft_strlen(flags->output);
	if (!flags->arg && flags->letter == 'c')
		output_len++;
	return (ret < 0 ? ret : output_len);
}
