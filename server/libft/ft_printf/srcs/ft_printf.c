/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/14 21:53:07 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 17:44:30 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	g_bufflen = 0;

int		ft_vsprintf(char **str, const char *format, va_list args)
{
	t_flags flags;
	int		ret;
	int		i;
	int		j;

	ret = 0;
	i = -1;
	j = 0;
	flags.arg_len = 0;
	flags.buff = str;
	while (++i > -1)
		if (format[i] == '%' || !format[i])
		{
			if (format[i] == '%')
				if (ftpf_process_arg(format + i + 1, &flags, args) < 0)
					return (-1);
			if (format[i] == '%')
				ret += flags.arg_len;
			ret += ftpf_concat_buff(format, &flags, i, j);
			if (!format[i] || (int)ft_strlen(format + i) < flags.flags_len)
				return (ret);
			j = i + flags.flags_len;
			i += flags.flags_len - 1;
		}
	return (ret);
}

int		ft_vfprintf(int fd, const char *format, va_list args)
{
	char	*str;
	int		ret;

	g_bufflen = 0;
	str = ft_memalloc((ft_strlen(format) + 1) * sizeof(char));
	ret = ft_vsprintf(&str, format, args);
	write(fd, str, g_bufflen);
	free(str);
	return (ret);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vfprintf(fd, format, args);
	va_end(args);
	return (ret);
}

int		ft_sprintf(char **str, const char *format, ...)
{
	va_list		args;
	int			ret;

	g_bufflen = 0;
	va_start(args, format);
	if (!*str)
		if (!(*str = ft_strdup("")))
			return (-1);
	ret = ft_vsprintf(str, format, args);
	va_end(args);
	*(*str + g_bufflen) = '\0';
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vfprintf(1, format, args);
	va_end(args);
	return (ret);
}
