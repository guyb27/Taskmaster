/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:00:23 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 03:23:07 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "heart.h"

# define WHITE "\033[7;49;37"
# define END "\033[0m"
# define HISTSIZE 500
# define HISTFILE "/.taskmaster_history"
# define HISTFILESIZE 500

typedef struct termios		t_termios;
typedef struct s_select		t_select;
typedef struct winsize		t_ws;
struct s_shell;

typedef struct	s_key
{
	char		key[4];
	int			(*f)(struct s_shell *sh, char key[3]);
}				t_key;

typedef struct	s_tab
{
	char		**cmd;
	char		**elem;
	char		*is_file;
	char		*before;
	char		*word;
	int			nb_word;
	int			nb_char;
	int			nb_line;
}				t_tab;

typedef struct	s_shell
{
	t_ws		ws;
	int			prompt_len;
	t_key		keys[100];
	char		*cmd;
	char		*tmp_line;
	t_tab		t;
	t_select	*sel;
	int			hist;
	int			tabu;
}				t_shell;

void			gm_goto(int nb, void (*f) (int, int), int len, int col);
void			ft_pushed_left(t_shell *sh);
void			ft_pushed_right(t_shell *sh);
void			init_tab_and_hist(t_shell *sh, char key[5]);
void			init_hist(t_shell *sh, char key[5]);
void			init_tab(t_shell *sh, char key[5]);
void			ft_putcmd(t_shell *sh, int new_pos);
int				ft_recup_cursor_pos(t_shell *sh, int *left_xpos,
		int *right_xpos);
int				ft_count_line_cmd(t_shell *sh);
int				ft_reprint_cmd(t_shell *sh);
char			*ft_get_user_input(void);
int				ft_input_check(char key[], char buff[]);
void			ft_init_input_keys(t_shell *sh);
void			ft_left_move(int len, int col);
void			ft_right_move(int len, int col);
int				ft_pushed_key_home_end(t_shell *sh, char key[]);
int				ft_pushed_key_altup_altdown(t_shell *sh, char key[]);
int				ft_pushed_key_altleft_altright(t_shell *sh, char key[]);
int				ft_pushed_key_backspace(t_shell *sh, char key[]);
int				ft_pushed_key_del(t_shell *sh, char key[]);
int				ft_pushed_key_enter(t_shell *sh, char key[]);
int				ft_pushed_left_right(t_shell *sh, char key[]);
int				ft_pushed_up_down(t_shell *sh, char key[]);
int				ft_pushed_key_tab(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_c(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_d(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_l(t_shell *sh, char key[]);
int				ft_init_shell_struct(t_shell *sh);
int				get_term_raw_mode(int mode);
void			ft_get_cols(t_ws *ws);
void			history_save(char ***history, char *news, int version, char *s);
void			history_get(t_shell *sh, char key[]);
int				termcap(char *str);

#endif
