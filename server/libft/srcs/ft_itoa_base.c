/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:15 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:26:00 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_valid_base(char *base)
{
	int i;
	int j;

	if (ft_strlen(base) < 2)
		return (0);
	i = -1;
	while (base[++i])
	{
		j = -1;
		while (base[++j])
			if ((i != j && base[i] == base[j]) ||
				base[i] == '+' || base[i] == '-' || !ft_isprint(base[i]))
				return (0);
	}
	return (1);
}

char		*ft_itoa_base(int n, char *base)
{
	char	*ret;
	int		len;
	int		baselen;

	baselen = ft_strlen(base);
	len = ft_intlen_base(n, baselen) + 1;
	if (!(ret = malloc((len + 1) * sizeof(char))) || !ft_is_valid_base(base))
		return (NULL);
	if (!n)
		*ret = base[0];
	if (n < 0)
	{
		if (baselen == 10)
			*ret = '-';
		n = -n;
	}
	ret[len - 1] = '\0';
	while (n)
	{
		len--;
		ret[len - 1] = base[n % baselen];
		n /= baselen;
	}
	return (ret);
}
