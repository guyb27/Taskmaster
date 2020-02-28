/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ftpf_apply_width_inner(t_flags *flags, char *fill, size_t strlen)
{
	char	*tmp;
	size_t	i;

	if (!(tmp = ft_strdup(flags->output)))
		return ;
	free(flags->output);
	if (!(flags->output = ft_memalloc((sizeof(char) * flags->width) + 1)))
		return ;
	i = flags->width - strlen;
	if (flags->arg && flags->sharp && i && flags->padding_left &&
														flags->letter == 'o')
		i--;
	if (flags->padding_left)
	{
		ft_strcat(flags->output, tmp);
		while (i--)
			ft_strcat(flags->output, fill);
	}
	else
	{
		while (i--)
			ft_strcat(flags->output, fill);
		ft_strcat(flags->output, tmp);
	}
	free(tmp);
}

int			ftpf_apply_width(t_flags *flags)
{
	size_t	strlen;
	char	*fill;

	fill = flags->zero_prefix && !flags->padding_left ? "0" : " ";
	if (ft_strchr("diouxX", flags->letter) && flags->point)
		fill = " ";
	strlen = ft_strlen(flags->output);
	if (flags->width > strlen)
		ftpf_apply_width_inner(flags, fill, strlen);
	if (flags->width && !flags->arg && flags->letter == 'c')
		(flags->output)[ft_strlen(flags->output) - 1] = '\0';
	return (1);
}
