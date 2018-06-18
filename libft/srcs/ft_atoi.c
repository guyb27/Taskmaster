/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:13 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:13 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (sign ? -res : res);
}
