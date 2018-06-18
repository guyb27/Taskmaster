/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:13 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/10 21:17:40 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_intlen(long n)
{
	long i;

	i = n < 0;
	while (n /= 10)
		i++;
	return (i + 1);
}
