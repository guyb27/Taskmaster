# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/23 15:29:21 by gbarnay      #+#   ##    ##    #+#        #
#    Updated: 2018/01/25 18:33:01 by gbarnay     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS += -Wall -Wextra -Werror
DIR_SRCS = .
DIR_INC = .

RAW_SRCS =	ft_memset.c		\
			ft_memcpy.c		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strdup.c		\
			ft_strcpy.c		\
			ft_strcat.c		\
			ft_strncat.c	\
			ft_strchr.c		\
			ft_strcmp.c		\
			ft_strncmp.c	\
			ft_isascii.c	\
			ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isupper.c	\
			ft_islower.c	\
			ft_tolower.c	\
			ft_isprint.c	\
			ft_atoi.c		\
			ft_memdel.c		\
			ft_strdel.c		\
			ft_strclr.c		\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strmap.c		\
			ft_strmapi.c	\
			ft_strequ.c		\
			ft_strnequ.c	\
			ft_strjoin.c	\
			ft_toupper.c	\
			ft_strsub.c		\
			ft_strnew.c		\
			ft_strnstr.c	\
			ft_memccpy.c	\
			ft_strtrim.c	\
			ft_isspace.c	\
			ft_memalloc.c	\
			ft_strsplit.c	\
			ft_putchar.c	\
			ft_strncpy.c	\
			ft_putstr.c		\
			ft_putendl.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_strlcat.c	\
			ft_memmove.c	\
			ft_strrchr.c	\
			ft_strstr.c		\
			ft_putnbr.c		\
			ft_intlen.c		\
			ft_intlen_base.c	\
			ft_u_intlen_base.c	\
			ft_itoa.c		\
			ft_strlen.c		\
			ft_bzero.c		\
			ft_lstnew.c		\
			ft_lstdelone.c	\
			ft_lstdel.c		\
			ft_lstadd.c		\
			ft_lstiter.c	\
			ft_lstmap.c		\
		ft_itoa_base.c		\
		ft_print_memory.c	\
		ft_math_sqrt.c		\
		ft_math_pow.c		\
		ft_math_factorial.c	\
		ft_math_isprime.c	\
		ft_math_nextprime.c	\
		ft_math_fibonacci.c	\
		ft_math_ceil.c		\
		ft_math_floor.c		\
		ft_abs.c			\
		ft_log.c			\
		ft_log_var.c		\
		ft_get_log_params.c	\
		ft_str_replace.c	\
		ft_strstr_int.c		\
		ft_read_file.c		\
		ft_print_bits.c		\
		ft_putwchar_fd.c	\
		ft_putwchar.c		\
		ft_putwstr_fd.c		\
		ft_putwstr.c		\
		ft_realloc.c		\
		ft_free_list.c

.PHONY: all clean fclean re

OBJS = $(RAW_SRCS:.c=.o)
SRCS = $(addprefix $(DIR_SRCS)/,$(RAW_SRCS))
NB_FILES = $(words $(RAW_SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@(printf "\033[1A" && printf "\033[K") # remove last line
	@echo "\033[92mCOMPILED:  libft.a\033[0m [100%]"
	@printf "\e[?25h" #show cursor

%.o: $(DIR_SRCS)/%.c libft.h
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@(printf "\e[?25l" && printf "\033[1A") # hide cursor & move up
	@echo "\033[93mCOMPILING: libft.a\033[0m [$(PERCENT)%]"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
