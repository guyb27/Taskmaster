/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_math_isprime.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:16 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 20:20:52 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_isprime(int nb)
{
	int i;
	int max_to_check;

	if (nb > FT_INT_MAX || nb < 2)
		return (0);
	else if (nb == 2)
		return (1);
	max_to_check = nb / 2;
	i = 3;
	while (i <= max_to_check)
	{
		if (!(nb % i))
			return (0);
		i += 2;
	}
	return (nb % 2 == 0 ? 0 : 1);
}
