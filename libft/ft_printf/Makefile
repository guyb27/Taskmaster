# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/23 15:29:21 by gbarnay      #+#   ##    ##    #+#        #
#    Updated: 2018/01/30 18:11:37 by gbarnay     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS += #-Wall -Wextra -Werror
DIR_SRCS = srcs
DIR_LIBFT = ../srcs

RAW_SRCS =	srcs/ft_printf.c			\
			srcs/ft_args_and_buff.c		\
			srcs/ft_flags.c				\
			srcs/ft_types.c				\
			srcs/ft_numbers_to_str.c	\
			srcs/ft_handlers.c			\
			srcs/ft_apply_precision.c	\
			srcs/ft_apply_width.c		\
			srcs/ft_apply_sharp.c		\
			srcs/ft_apply_patches.c		\
			srcs/ft_parse_flags.c		\
			srcs/ft_wchar.c				\
			srcs/ft_bonus.c

.PHONY: all clean fclean re

OBJS = $(RAW_SRCS:.c=.o)
SRCS = $(addprefix $(DIR_SRCS)/,$(RAW_SRCS))
NB_FILES = $(words $(RAW_SRCS))

all: $(NAME)

$(NAME): libft.a $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@(printf "\033[1A" && printf "\033[K") # remove last line
	@echo "\033[92mCOMPILED:  libftprintf.a\033[0m [100%]"
	@printf "\e[?25h" #show cursor

$(DIR_SRCS)/%.o: $(DIR_SRCS)/%.c $(DIR_SRCS)/ft_printf.h
	@$(eval CURSOR=$(shell echo $$(($(CURSOR)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR)*100/$(NB_FILES)))))
	@(printf "\e[?25l" && printf "\033[1A") # hide cursor & move up
	@echo "\033[93mCOMPILING: libftprintf.a\033[0m [$(PERCENT)%]"
	@$(CC) $(CFLAGS) -c -o $@ $<

libft.a:
	@make -C $(DIR_LIBFT)
	@cp $(DIR_LIBFT)/libft.a ./$(NAME)
	@echo ""

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -f $(DIR_LIBFT)/libft.a
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
