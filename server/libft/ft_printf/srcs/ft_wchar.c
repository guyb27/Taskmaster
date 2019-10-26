/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wchar.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 21:37:29 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 18:36:53 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_check_wchar(wchar_t c)
{
	if (c > 0x10FFFF || c < 0 ||
		(c >= 0xD800 && c <= 0xDFFF) ||
		(MB_CUR_MAX == 1 && c > 255))
		return (0);
	return (1);
}

void	ftpf_append_wchar(char *str, wchar_t c)
{
	size_t	strlen;

	strlen = ft_strlen(str);
	if (c <= 0x7F || MB_CUR_MAX == 1)
		str[ft_strlen(str)] = c;
	else if (c <= 0x7FF || MB_CUR_MAX == 2)
	{
		str[strlen] = (c >> 6) + 0xC0;
		str[strlen + 1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF || MB_CUR_MAX == 3)
	{
		str[strlen] = (c >> 12) + 0xE0;
		str[strlen + 1] = ((c >> 6) & 0x3F) + 0x80;
		str[strlen + 2] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		str[strlen] = (c >> 18) + 0xF0;
		str[strlen + 1] = ((c >> 12) & 0x3F) + 0x80;
		str[strlen + 2] = ((c >> 6) & 0x3F) + 0x80;
		str[strlen + 3] = (c & 0x3F) + 0x80;
	}
}

size_t	ftpf_wcslen(const wchar_t *s)
{
	const wchar_t *p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}
