# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/23 15:29:21 by gbarnay      #+#   ##    ##    #+#        #
#    Updated: 2018/06/11 17:45:14 by gbarnay     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
DIR_SRCS = srcs
DIR_PRINTF = ft_printf
DIR_GNL = get_next_line
FLAGS = -I $(DIR_PRINTF)/srcs/ -I $(DIR_GNL)

all: $(NAME)

$(NAME): libprintf.a $(DIR_GNL)/get_next_line.o
	@cp $(DIR_PRINTF)/libftprintf.a $(NAME)
	@ar rcs $(NAME) $(DIR_GNL)/get_next_line.o
	@echo "\033[95m>> libft.a is ready <<\033[0m"

libprintf.a:
	@echo "Please wait..."
	@rm -rf $(DIR_PRINTF)/libftprintf.a
	@make -C $(DIR_PRINTF)

$(DIR_GNL)/get_next_line.o:
	@echo "\033[93mCOMPILING: get_next_line\033[0m [50%]"
	@gcc -c $(DIR_GNL)/get_next_line.c -o $(DIR_GNL)/get_next_line.o
	@(printf "\033[1A" && printf "\033[K") # remove last line
	@echo "\033[92mCOMPILED:  get_next_line\033[0m [100%]"

clean:
	@echo "\033[91mobjects files removed\033[0m"
	@(cd $(DIR_PRINTF) && make -s clean $@)
	@rm -f $(DIR_GNL)/get_next_line.o

fclean: clean
	@echo "\033[91mlibft.a removed\033[0m"
	@(cd $(DIR_PRINTF) && make -s fclean $@)
	@rm -f $(NAME)

re: fclean all
