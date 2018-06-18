/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_math_fibonacci.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:16 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:16 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_math_fibonacci(int index)
{
	if (!index)
		return (0);
	else if (index < 0)
		return (-1);
	else if (index > 1)
		return (ft_math_fibonacci(index - 1) + ft_math_fibonacci(index - 2));
	else
		return (1);
}
