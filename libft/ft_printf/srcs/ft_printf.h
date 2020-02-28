/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:05:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:05:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../srcs/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdio.h>

/*
**	# include <inttypes.h>
**	# include <sys/types.h>
**	# include <stdint.h>
**	# include <locale.h>
*/

extern size_t	g_bufflen;

typedef struct			s_flags
{
	intmax_t			arg;
	double				float_arg;
	int					zero_prefix;
	int					padding_left;
	int					show_sign;
	int					blank_sign;
	int					sharp;
	int					point;
	unsigned int		width;
	unsigned int		precision;
	enum {
		none,
		hh,
		h,
		ll,
		l,
		j,
		z
	}					length;
	int					flags_len;
	int					arg_len;
	char				letter;
	char				*output;
	char				**buff;
}						t_flags;

/*
**	ft_apply_precision.c
*/
int						ftpf_apply_precision_str(t_flags *flags);
int						ftpf_apply_precision_numbers(t_flags *flags);
int						ftpf_apply_precision_pointer(t_flags *flags);

/*
**	ft_apply_width.c
*/
int						ftpf_apply_width(t_flags *flags);

/*
**	ft_apply_sharp.c
*/
int						ftpf_apply_sharp_octal(t_flags *flags);
int						ftpf_apply_sharp_hex(t_flags *flags);

/*
**	ft_apply_patches.c
*/
void					ftpf_patch_upper_letter(t_flags *flags);
void					ftpf_patch_sign_pos(t_flags *flags);
int						ftpf_apply_sign(t_flags *flags);

/*
**	ft_printf.c
*/
int						ft_vfprintf(int fd, const char *format, va_list args);
int						ft_fprintf(int fd, const char *format, ...);
int						ft_sprintf(char **str, const char *format, ...);
int						ft_printf(const char *format, ...);

/*
**	ft_args_and_buff.c
*/
int						ftpf_concat(t_flags *flags, const char *str,
																size_t size);
int						ftpf_concat_buff(const char *format, t_flags *flags,
																int i, int j);
int						ftpf_process_arg(const char *format, t_flags *flags,
																va_list args);

/*
**	ft_parse_flags.c
*/
int						ftpf_parse_width(const char *format, t_flags *flags,
																va_list args);
int						ftpf_parse_precision(const char *format, t_flags *flags,
																va_list args);
void					ftpf_parse_flags(const char *format, t_flags *flags,
																va_list args);
int						ftpf_exec_args_func(t_flags *flags);
int						ftpf_get_str_arg(t_flags *flags);

/*
**	ft_handlers.c
*/
int						ftpf_handle_char(t_flags *flags);
int						ftpf_handle_str(t_flags *flags);
int						ftpf_handle_pointer(t_flags *flags);
int						ftpf_handle_numbers(t_flags *flags);

/*
**	ft_wchar.c
*/
int						ftpf_check_wchar(wchar_t c);
void					ftpf_append_wchar(char *str, wchar_t c);
size_t					ftpf_wcslen(const wchar_t *s);

/*
**	ft_flags.c
*/
void					ftpf_debug_flags(t_flags *flags);
void					ftpf_flags_init(t_flags *flags);
int						ftpf_flags_format(const char *s, t_flags *flags);
int						ftpf_flags_width(const char *s, t_flags *flags);
int						ftpf_flags_precision(const char *s, t_flags *flags);
int						ftpf_flags_length(const char *s, t_flags *flags);

/*
**	ft_types.c
*/
intmax_t				ftpf_get_float_from_len(t_flags *flags);
intmax_t				ftpf_get_signed_from_len(t_flags *flags);
intmax_t				ftpf_get_u_from_len(t_flags *flags);

/*
**	ft_numbers_to_str.c
*/
char					*ftpf_dtoa(double n, unsigned int precision);
char					*ftpf_l_itoab(intmax_t n, char *base);
char					*ftpf_ul_itoab(uintmax_t n, char *base);

/*
**	ft_bonus.c
*/
int						ftpf_handle_str_non_printable(t_flags *flags);
int						ftpf_patch_colors(char *format, char *modifier,
																t_flags *flags);
int						ftpf_memcpy_modifiers(char *format, t_flags *flags,
																int size);

#endif
