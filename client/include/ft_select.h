/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 06:59:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "heart.h"

# define BOLD "\x1b[1m"
# define UNDER "\x1b[4m"
# define REV "\x1b[7m"

# define IGREY "\x1b[40m"
# define IRED "\x1b[41m"
# define IGREEN "\x1b[42m"
# define IYELLOW "\x1b[43m"
# define IBLUE "\x1b[44m"
# define IPURPLE "\x1b[45m"
# define ICYAN "\x1b[46m"
# define IWHITE "\x1b[47m"

typedef struct s_shell	t_shell;
typedef struct termios	t_term;
typedef struct winsize	t_ws;
typedef struct s_tab	t_tab;

typedef struct			s_line
{
	char				*elem;
	int					x_char_pos;
	int					x_param_pos;
	int					y_pos;
	int					is_file;
	int					ds;
	int					cursor_inside;
	struct s_line		*prev;
	struct s_line		*next;
}						t_line;

typedef struct			s_tablex
{
	char				c;
	int					i;
	int					count;
}						t_tab_lex;

typedef struct			s_select
{
	t_ws				ws;
	char				*ret;
	int					pose_min;
	int					bp;
	int					pbl;
	int					nbl;
	int					nbp;
	char				*ds;
	t_line				*line;
}						t_select;

int						ft_select(t_shell **ed, int version, char key[]);
void					ft_print_params(t_select *sel);
int						ft_manage_touch(t_shell **ed, int version, char key[]);
int						ft_arrows(char arrows, t_select **t, int *place);
void					ft_init_select(t_shell **ed);
int						ft_count_line(t_select *t);
int						lexer_tab(t_shell **sh);
int						ft_search_big_param(t_line *line);
int						search_bin_tab(t_shell **ed);
int						search_in_rep_tab(t_shell **ed);
void					ft_first_sort(t_line **line, char *av);
int						ft_count_params(t_line *line);
int						ft_char_by_line(t_select **sel);
int						ft_params_by_line(t_select *t);
void					ft_print_select(t_line *str, int j, int bp, int v);
void					ft_place_cursor(int nb_ret, int len_line, int v);
void					place_cursor_before(t_shell *sh);
void					place_cursor_after(t_shell *sh);
int						ft_free_t_select(t_select **t);
int						tabulator(t_shell **ed, int version, char key[]);
char					**ft_tabsplit(void);
int						replace_line_after_tab(t_shell **ed);
void					ft_free_t_tab(t_tab *t);
int						lex_tab(const char *s, int i, int *find, int *cursor);
void					binorfile(t_shell **ed, int *end_word);

#endif
