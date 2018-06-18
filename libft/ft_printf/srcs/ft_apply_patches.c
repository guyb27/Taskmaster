/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_apply_patches.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 20:17:57 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/21 21:13:55 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			ftpf_patch_upper_letter(t_flags *flags)
{
	if (ft_isupper(flags->letter)
			&& ft_strchr("sSpdDioOuUxXcCfF%", flags->letter))
	{
		if (flags->letter != 'X')
		{
			flags->length = l;
			flags->letter = ft_tolower(flags->letter);
		}
	}
}

/*
**	if a negative number is filled up with 0's (with width + 0 flag),
**	move '-' (or '+' if sign flag active) to start
*/

void			ftpf_patch_sign_pos(t_flags *flags)
{
	int	i;
	int	spaces;

	if (!flags->precision && !flags->zero_prefix)
		return ;
	spaces = 0;
	while ((flags->output)[spaces] == ' ')
		spaces++;
	i = spaces;
	while ((flags->output)[i] == '0' && (flags->output)[i + 1])
		i++;
	if (i > 1 && flags->letter == 'p' && (flags->output)[i] == 'x')
	{
		(flags->output)[i] = '0';
		(flags->output)[1 + spaces] = 'x';
	}
	if (i && i != spaces && ((flags->output)[i] == '-' ||
				(flags->output)[i] == '+'))
	{
		(flags->output)[spaces] = (flags->output)[i] == '-' ? '-' : '+';
		(flags->output)[i] = '0';
	}
}

static void		ftpf_apply_sign_expand(t_flags *flags, char sign)
{
	char	*tmp;

	tmp = ft_strdup(flags->output);
	free(flags->output);
	flags->output = ft_memalloc(sizeof(char) * (ft_strlen(tmp) + 1));
	(flags->output)[0] = sign;
	ft_strcat(flags->output, tmp);
	free(tmp);
	if (flags->width && ft_strlen(flags->output) > flags->width &&
			(flags->output)[ft_strlen(flags->output) - 1] == ' ')
		(flags->output)[ft_strlen(flags->output) - 1] = '\0';
}

int				ftpf_apply_sign(t_flags *flags)
{
	int		i;
	char	sign;

	if ((int)flags->arg < 0)
		return (1);
	sign = flags->show_sign ? '+' : ' ';
	if ((flags->show_sign || flags->blank_sign))
	{
		i = 0;
		while ((flags->output)[i] == ' ' && !ft_isdigit((flags->output)[i + 1]))
			i++;
		if ((flags->output)[i] == '-')
			return (1);
		else if ((flags->output)[i] == ' ' || ((flags->output)[i] == '0' &&
					ft_isdigit((flags->output)[i + 1]) && !flags->precision))
			(flags->output)[i] = sign;
		else
			ftpf_apply_sign_expand(flags, sign);
	}
	return (1);
}
