/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_math_nextprime.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:17 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 20:21:13 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_nextprime(int nb)
{
	while (nb < FT_INT_MAX)
	{
		if (ft_math_isprime(nb))
			return (nb);
		nb++;
	}
	return (0);
}
