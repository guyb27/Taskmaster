/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_apply_precision.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/11 11:49:47 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/21 21:03:02 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_apply_precision_str(t_flags *flags)
{
	int i;

	if (!flags->precision && flags->point)
		(flags->output)[0] = '\0';
	else if (flags->length && ft_strlen(flags->output) > flags->precision)
	{
		i = flags->precision;
		while ((unsigned char)(flags->output)[i] <= 0xBF &&
				(unsigned char)(flags->output)[i] > 0x7F && i)
			i--;
		(flags->output)[i] = '\0';
	}
	else if (ft_strlen(flags->output) > flags->precision)
		(flags->output)[flags->precision] = '\0';
	return (1);
}

int		ftpf_apply_precision_numbers(t_flags *flags)
{
	size_t	strlen;
	size_t	i;
	char	*tmp;

	strlen = ft_strlen(flags->output);
	strlen -= (flags->output)[0] == '-' ? 1 : 0;
	if (!flags->arg && flags->point && !flags->precision)
		flags->output[0] = '\0';
	else if (strlen < flags->precision)
	{
		i = flags->precision - ft_strlen(flags->output);
		if (ft_strchr(flags->output, '-'))
			i++;
		tmp = ft_strdup(flags->output);
		free(flags->output);
		if (!(flags->output = ft_memalloc(
						sizeof(char) * (flags->precision + 1))))
			return (0);
		while (i--)
			ft_strcat(flags->output, "0");
		ft_strcat(flags->output, tmp);
		free(tmp);
	}
	return (1);
}

int		ftpf_apply_precision_pointer(t_flags *flags)
{
	int		diff;
	char	*tmp;

	if (!flags->arg && !flags->precision)
		(flags->output)[2] = '\0';
	else if (flags->precision)
	{
		diff = flags->precision - (ft_strlen(flags->output) - 2);
		if (diff > 0)
		{
			tmp = ft_strdup(flags->output);
			free(flags->output);
			if (!(flags->output = ft_memalloc(
							(sizeof(char) * (ft_strlen(tmp) + diff + 1)))))
				return (0);
			ft_strcat(flags->output, "0x");
			while (diff--)
				ft_strcat(flags->output, "0");
			ft_strcat(flags->output, (tmp + 2));
			free(tmp);
		}
	}
	return (1);
}
