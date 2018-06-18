/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_handlers.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 16:51:22 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 18:35:58 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ftpf_handle_char(t_flags *flags)
{
	flags->output = (char*)ft_memalloc(sizeof(wchar_t) * 2);
	if (flags->length)
		if (!ftpf_check_wchar((wchar_t)flags->arg))
			return (-1);
	if (!flags->length || MB_CUR_MAX == 1)
		(flags->output)[0] = (char)flags->arg;
	else
	{
		ftpf_append_wchar(flags->output, (wchar_t)flags->arg);
	}
	return (1);
}

int			ftpf_handle_str(t_flags *flags)
{
	wchar_t			*lstr;
	unsigned int	i;

	if (!flags->arg)
		flags->output = ft_strdup("(null)");
	else if (!flags->length)
		flags->output = ft_strdup((char*)flags->arg);
	else
	{
		lstr = (wchar_t*)flags->arg;
		if (!(flags->output = ft_memalloc(
					sizeof(wchar_t) * (ftpf_wcslen((const wchar_t*)lstr) + 1))))
			return (-1);
		i = 0;
		while (*lstr)
		{
			if ((!flags->point || (++i < flags->precision)) &&
					!ftpf_check_wchar(*lstr))
				return (-1);
			ftpf_append_wchar(flags->output, *lstr++);
		}
	}
	if (flags->point)
		ftpf_apply_precision_str(flags);
	return (1);
}

static void	ftpf_put_pointer_hex(uintmax_t octet, int rem, char *buffer)
{
	char *base;

	base = "0123456789abcdef";
	if (rem > 1)
		ftpf_put_pointer_hex(octet >> 4, rem - 1, buffer);
	buffer[rem + 1] = base[octet % 16];
}

int			ftpf_handle_pointer(t_flags *flags)
{
	int i;
	int j;

	flags->output = ft_memalloc(15);
	ft_strcat(flags->output, "0x");
	ftpf_put_pointer_hex((uintmax_t)flags->arg, 12, flags->output);
	i = 2;
	while ((flags->output)[i] == '0' && (flags->output)[i + 1])
		i++;
	j = 2;
	while ((flags->output)[i])
		(flags->output)[j++] = (flags->output)[i++];
	(flags->output)[j] = '\0';
	if (!flags->arg)
		(flags->output)[3] = '\0';
	if (flags->point)
		ftpf_apply_precision_pointer(flags);
	return (1);
}

int			ftpf_handle_numbers(t_flags *flags)
{
	char	*str;

	str = NULL;
	if (flags->letter == 'd' || flags->letter == 'i')
		str = ftpf_l_itoab(ftpf_get_signed_from_len(flags), "0123456789");
	else if (flags->letter == 'u')
		str = ftpf_ul_itoab(ftpf_get_u_from_len(flags), "0123456789");
	else if (flags->letter == 'x')
		str = ftpf_ul_itoab(ftpf_get_u_from_len(flags), "0123456789abcdef");
	else if (flags->letter == 'X')
		str = ftpf_ul_itoab(ftpf_get_u_from_len(flags), "0123456789ABCDEF");
	else if (flags->letter == 'o')
		str = ftpf_ul_itoab(ftpf_get_u_from_len(flags), "01234567");
	else if (flags->letter == 'f')
		str = ftpf_dtoa(flags->float_arg, flags->precision);
	else if (flags->letter == 'b')
		str = ftpf_ul_itoab(ftpf_get_u_from_len(flags), "01");
	flags->output = str;
	if (flags->point)
		ftpf_apply_precision_numbers(flags);
	return (1);
}
