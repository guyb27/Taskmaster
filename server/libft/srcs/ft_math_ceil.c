/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_math_ceil.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:16 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:16 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

double		ft_math_ceil(double nb)
{
	int	int_nb;

	int_nb = nb;
	if (nb < 0)
		return (int_nb);
	if ((double)int_nb == nb)
		return (nb);
	return (int_nb + 1);
}
