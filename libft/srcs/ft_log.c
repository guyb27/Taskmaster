/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_log.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:15 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:15 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
**	LOG LEVEL
**	--------------
** The ALL has the lowest possible rank and is intended to turn on all logging.
** The DEBUG Level designates fine - grained informational events that are most
**		useful to debug an application.
** The ERROR level designates error events that might still allow the
**		application to continue running.
** The FATAL level designates very severe error events that will presumably
**		lead the application to abort.
** The INFO level designates informational messages that highlight the progress
**		of the application at coarse - grained level.
** The OFF has the highest possible rank and is intended to turn off logging.
** The TRACE Level designates finer -grained informational events than the DEBUG
** TRACE level integer value. //removed for now
** The WARN level designates potentially harmful situations.
*/

int	g_log_lvl = 5;

/*
**	ft_log() && ft_log_int()
**	------------------
**	Use ft_log() to print simple debug/error.. messages
**	Use ft_log_int() to print debug/error.. messages with int using %d
**
**	Exemples :
**	ft_log(DEBUG, __func__, "jadore debug\n");
**	ft_log_int(DEBUG, __func__, "je debug un int : %d\n", my_int);
**	ft_log(ERROR, __func__, "Nous avons un probleme\n");
*/

static void	ft_putlog(const char *func, char *log, char *fcolor, char *bcolor)
{
	ft_putstr(KBOLD);
	ft_putstr(bcolor);
	ft_putstr(log);
	ft_putstr(BRESET""KRESET" ");
	ft_putstr(__TIME__" "KUNDER);
	ft_putstr(func);
	ft_putstr("():");
	ft_putstr(fcolor);
	ft_putstr(KRESET" ");
	ft_putstr(fcolor);
}

void		ft_log(int log_lvl, const char *func, char *message)
{
	if (!g_log_lvl || log_lvl == g_log_lvl)
	{
		ft_putstr(KRESET""BRESET);
		if (log_lvl == 1)
			ft_putlog(func, "DEBUG_:", KYEL, BDYEL);
		else if (log_lvl == 2)
			ft_putlog(func, "ERROR_:", KCRED, BRED);
		else if (log_lvl == 3)
			ft_putlog(func, "FATAL_:", KLMAG, BMAG);
		else if (log_lvl == 4)
			ft_putlog(func, "INFO_:", KLGRN, BDGRN);
		else if (log_lvl == 6)
			ft_putlog(func, "TRACE_:", KDGREY, BDGREY);
		else if (log_lvl == 7)
			ft_putlog(func, "WARN_:", KORANGE, BORANGE);
		ft_putstr(message);
	}
}
