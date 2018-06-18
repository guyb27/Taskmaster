/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_apply_sharp.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 17:51:01 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/21 21:05:56 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int				ftpf_apply_sharp_octal(t_flags *flags)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (!ft_isdigit((flags->output)[i]) && (flags->output)[i + 1])
		i++;
	if ((flags->output)[i] != '0' && i > 0)
		(flags->output)[i - 1] = '0';
	else if ((flags->output)[i] != '0')
	{
		tmp = ft_strdup(flags->output);
		free(flags->output);
		flags->output = ft_memalloc(sizeof(char) * (ft_strlen(tmp) + 1));
		(flags->output)[0] = '0';
		ft_strcat(flags->output, tmp);
		free(tmp);
	}
	return (1);
}

static int		ftpf_isdigit_hex(char c)
{
	if (ft_toupper(c) >= 'A' && ft_toupper(c) <= 'F')
		return (1);
	return (ft_isdigit(c));
}

static void		ftpf_expand_sharp(t_flags *flags)
{
	char	*tmp;

	tmp = ft_strdup(flags->output);
	free(flags->output);
	flags->output = ft_memalloc(sizeof(char) * (ft_strlen(tmp) + 1));
	(flags->output)[0] = '0';
	(flags->output)[1] = flags->letter == 'x' ? 'x' : 'X';
	ft_strcat(flags->output, tmp);
	free(tmp);
	if (flags->padding_left && ft_strlen(flags->output) > flags->width)
		(flags->output)[ft_strlen(flags->output) - 2] = '\0';
}

int				ftpf_apply_sharp_hex(t_flags *flags)
{
	size_t	i;

	i = 0;
	while ((flags->output)[i] && !ftpf_isdigit_hex((flags->output)[i]))
		i++;
	if (i > 0)
	{
		(flags->output)[i - 2] = '0';
		(flags->output)[i - 1] = flags->letter == 'x' ? 'x' : 'X';
	}
	else if (flags->arg)
	{
		if ((flags->output)[0] == '0' && (flags->output)[1] == '0'
				&& !flags->precision)
			(flags->output)[1] = flags->letter == 'x' ? 'x' : 'X';
		else
			ftpf_expand_sharp(flags);
	}
	return (1);
}
