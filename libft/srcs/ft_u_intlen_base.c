/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:13 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/18 19:59:40 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_u_intlen_base(unsigned long long n, int base_len)
{
	unsigned long long i;

	if (base_len < 2)
		return (1);
	i = 0;
	while (n /= base_len)
		i++;
	return (i + 1);
}
