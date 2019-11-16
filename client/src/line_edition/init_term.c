/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/26 09:03:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 09:26:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int						ft_init_shell_struct(t_shell *sh, t_prompt *prompt)
{
	g_cl.cmd = NULL;
	g_cl.cursor_pos = 0;
	sh->tmp_line = NULL;
	sh->tabu = -1;
	sh->hist = -2;
	sh->prompt_len = 13;
	sh->sel = NULL;
	sh->t.cmd = NULL;
	sh->t.elem = NULL;
	sh->t.is_file = NULL;
	sh->t.before = NULL;
	sh->t.word = NULL;
	sh->t.nb_word = 0;
	sh->t.nb_line = 0;
	sh->t.nb_char = 0;
	ft_get_cols(&sh->ws);
	return (0);
}

int						get_term_raw_mode(int mode)
{
	t_termios			term;
	static int			i = 0;
	static t_termios	test;

	if (i == 0)
	{
		ft_memset(&test, 0, sizeof(t_termios));
		tcgetattr(STDIN_FILENO, &test);
	}
	if (mode)
	{
		ft_memset(&term, 0, sizeof(t_termios));
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~(ECHO | ICANON | ISIG);
		term.c_oflag &= ~(OPOST);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	}
	else
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &test);
	mode ? TERMCAP("ns") : 0;
	i = 1;
	return (1);
}
