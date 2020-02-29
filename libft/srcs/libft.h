/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 04:19:59 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

/*
**	Read files
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
**	Math
*/
# define FT_INT_MIN		-2147483648
# define FT_INT_MAX		2147483647
# define FT_ULONG_MAX	18446744073709551615
# define FT_DBL_MAX		709.782712893384
# define FT_PI			3.1415926535897932384626433832795
# define FT_PRECISION	1E-16

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
enum			e_log_level {ALL, DEBUG, ERROR, FATAL, INFO, OFF, TRACE, WARN};
extern int		g_log_lvl;

# define FUNC		__func__
# define LINE		__LINE__

/*
**	Console Text Style
*/
# define KBOLD		"\e[1m"
# define KDIM		"\e[2m"
# define KUNDER		"\e[4m"
# define KBLINK		"\e[5m"
# define KREV		"\e[7m"
# define KHIDDEN	"\e[8m"

/*
**	Console colors
*/
# define KRED		"\e[31m"
# define KLRED		"\e[91m"
# define KGRN		"\e[32m"
# define KYEL		"\e[33m"
# define KBLUE		"\e[34m"
# define KMAG		"\e[35m"
# define KCYN		"\e[36m"
# define KDGREY		"\e[90m"
# define KLGRN		"\e[92m"
# define KLYEL		"\e[93m"
# define KLMAG		"\e[95m"
# define KLCYN		"\e[96m"
# define KORANGE	"\e[38;5;208m"
# define KCRED		"\e[38;5;196m"

# define KRESET		"\e[0m"
# define KRESBOLD	"\e[21m"
# define KRESUNDER	"\e[24m"
# define KRESREV	"\e[27m"

/*
**	Console Background colors
*/
# define BRED		"\e[41m"
# define BGRN		"\e[42m"
# define BYEL		"\e[43m"
# define BBLUE		"\e[44m"
# define BMAG		"\e[45m"
# define BLBLUE		"\e[104m"
# define BDGRN		"\e[48;5;28m"
# define BORANGE	"\e[48;5;202m"
# define BDGREY		"\e[48;5;237m"
# define BDYEL		"\e[48;5;94m"

# define BRESET		"\e[49m"

/*
**	Structures
*/
typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_vector3
{
	int				x;
	int				y;
	int				z;
}					t_vector3;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** First Part
*/
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(char *src);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t n);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Second Part
*/
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(intmax_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(intmax_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** Bonus
*/
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new_elem);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** My Bonus --------------------------------------------------------------------
*/
void				ft_putwchar_fd(wchar_t c, int fd);
void				ft_putwchar(wchar_t c);
void				ft_putwstr_fd(wchar_t const *str, int fd);
void				ft_putwstr(wchar_t const *str);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isspace(int c);
int					ft_intlen(long long n);
int					ft_intlen_base(long n, int base_len);
int					ft_u_intlen_base(unsigned long long n, int base_len);
char				*ft_itoa_base(int n, char *base);
void				*ft_print_memory(void *addr, unsigned int size);
void				ft_print_bits(char octet);
void				*ft_realloc(void *ptr, size_t size);
void				ft_free_list(char **list);

char				*ft_read_file(char *file_path, int buff_size);
/*
**	Math
*/
int					ft_math_sqrt(int nb);
int					ft_math_pow(int nb, int power);
int					ft_math_factorial(int nb);
int					ft_math_isprime(int nb);
int					ft_math_nextprime(int nb);
int					ft_math_fibonacci(int index);
double				ft_math_ceil(double nb);
double				ft_math_floor(double nb);
int					ft_abs(int n);
/*
**	Log system
*/
void				ft_log(int log_lvl, const char *func, char *message);
void				ft_log_var(int log_lvl, const char *func, char *message,
								void *var);
int					ft_get_log_params(int *argc, char *argv[]);
char				*ft_str_replace(char *haystack, char *needle,
									char *new_word);
int					ft_strstr_int(const char *haystack, const char *needle);
void				ft_logx(int log_level, char *msg, char *x);

#endif
