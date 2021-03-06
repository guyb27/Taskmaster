/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:54:42 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:20:57 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_select.h"

t_line		*ft_prepare_print(int i[2], t_line *line, int nb_line)
{
	int		at_print;
	t_line	*tmp;
	int		bp;

	bp = ft_search_big_param(line);
	tmp = line;
	at_print = i[0] + (nb_line * i[1]);
	while (at_print && tmp->next)
	{
		tmp = tmp->next;
		at_print--;
	}
	tmp->x_char_pos = i[1] * bp + i[1];
	tmp->x_param_pos = i[1];
	tmp->y_pos = i[0];
	return (tmp);
}

void		ft_place_cursor(int nb_ret, int len_line, int v)
{
	if (nb_ret > 0)
	{
		if (v == 0)
			tputs(tgoto(tgetstr("UP", NULL), 0, nb_ret), 1, ft_putchar);
		else if (v == 1)
			tputs(tgoto(tgetstr("DO", NULL), 0, nb_ret), 1, ft_putchar);
	}
	if (len_line > 0)
	{
		if (v == 0)
			tputs(tgoto(tgetstr("LE", NULL), 0, len_line), 1, ft_putchar);
		else if (v == 1)
			tputs(tgoto(tgetstr("RI", NULL), 0, len_line), 1, ft_putchar);
	}
}

void		ft_print_select(t_line *str, int j, int bp, int v)
{
	int		sp;

	sp = 0;
	j > 0 ? ft_putstr(" ") : 0;
	if (str->is_file)
	{
		if (str->is_file == 1 || str->is_file == 2)
			str->is_file == 1 ? ft_putstr(GREEN) : ft_putstr(RED);
		str->is_file == 3 ? ft_putstr(WHITE) : 0;
	}
	ft_putstr(BOLD);
	str->cursor_inside == 1 ? ft_putstr(IBLUE) : 0;
	str->cursor_inside == 1 ? tputs(tgetstr("us", NULL), 1, ft_putchar) : 0;
	ft_putstr(str->elem);
	sp = bp - ft_strlen(str->elem);
	while (sp > 0)
	{
		ft_putstr(" ");
		sp--;
	}
	str->cursor_inside == 1 && v == 1 ?
		tputs(tgetstr("ue", NULL), 1, ft_putchar) : 0;
	ft_putstr(END);
}

void		ft_print_params(t_select *t)
{
	int		i[2];

	i[0] = t->pose_min;
	i[1] = 0;
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (i[0] < t->nbl)
	{
		if (i[0] < t->ws.ws_row + t->pose_min)
		{
			i[0] > t->pose_min ? termcap("sf") : 0;
			termcap("cr");
		}
		i[1] = -1;
		while (++i[1] < t->pbl && i[0] + (t->nbl * i[1]) < t->nbp)
		{
			if (i[0] < t->ws.ws_row + t->pose_min)
				ft_print_select(ft_prepare_print(i, t->line, t->nbl),
				i[1], t->bp, 1);
			else
				ft_prepare_print(i, t->line, t->nbl);
		}
		i[0]++;
	}
	termcap("cr");
	ft_place_cursor(i[0] - 1, 0, 0);
}
