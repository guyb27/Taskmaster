# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2020/02/29 03:28:49 by gmadec           ###   ########lyon.fr    #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = cl_taskmaster

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wunused -Wunreachable-code
CPPFLAGS = -I ./include/
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			heart/cl_task.c \
			heart/utils.c \
			heart/ft_get_tab_elems.c \
			init/init_shell.c \
			init/utils.c \
			ft_select/ft_arrows.c \
			ft_select/ft_lex_tab.c \
			ft_select/ft_manage_count.c \
			ft_select/ft_first_sort.c \
			ft_select/ft_init_select.c \
			ft_select/ft_manage_touch.c \
			ft_select/ft_print_params.c \
			ft_select/ft_search.c \
			ft_select/ft_select.c \
			ft_select/tabulator.c \
			ft_select/ft_manage_tab.c \
			ft_select/ft_tabsplit.c \
			ft_select/utils.c \
			line_edition/init_term.c \
			line_edition/get_user_input.c \
			line_edition/utils_tab_and_hist.c \
			line_edition/ft_inputs.c \
			line_edition/ft_inputs_arrows.c \
			line_edition/ft_inputs_ctrl.c \
			line_edition/ft_inputs_del.c \
			line_edition/utils.c \
			line_edition/ft_manage_history.c \
			line_edition/ft_save_history.c \
			line_edition/cursor.c

OBJS_FOLDERS = 	\
				heart init ft_select line_edition

OBJS_NAME = $(SRCS_NAME:.c=.o)
DEPS_NAME = $(SRCS_NAME:.c=.d)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
DEPS = $(addprefix $(OBJS_PATH),$(DEPS_NAME))
OBJS_FOLDERS_BIS = $(addprefix $(OBJS_PATH),$(OBJS_FOLDERS))

NB_FILES = $(words $(SRCS_NAME))
SHELL = /bin/bash # just because sh print -n from echo
COLS = $(shell tput cols)
DEL_DSYMFILE = $(shell [ -e a.out.dSYM ] && echo rm -rf a.out.dSYM)

all: $(NAME)

$(NAME): init lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@printf "\e[?25h"	# set cursor to visible
	@tput setaf 10 	# set green color
	@tput bold
	@$(eval CURSOR := $(if $(CURSOR),$(CURSOR),0)) # is CURSOR var set ?
	@echo -n "[ $(NAME)    ] Compiled $(CURSOR)/$(NB_FILES) files."
	@tput sgr0 	# reset color
	@tput el 	# clear from cursor to end of line
	@echo ""
	@tput el 	# clear from cursor to end of line

init:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@tput cuu 4

-include $(DEPS)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell printf "[%3d/%3d - \e[1m\e[93m%3d%%\e[0m]" $(CURSOR) $(NB_FILES) $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@$(eval LOADSIZE=$(shell echo $$(($(CURSOR) * $(COLS) / $(NB_FILES)))))
	@printf "\e[?25l\e[s\e[35m\e[44m"
	@tput setaf $$((($(CURSOR)%7)+9))
	@number=1 ; while [[ $$i -le $(LOADSIZE)-1 ]] ; do \
        	printf "▌" ; \
        	((i = i + 1)) ; \
    	done
	@printf "\e[0K\e[0m\n\e[1m\e[93m"
	@echo -n "[ $(NAME) ] Compiling: "
	@printf "\e[0m"			# reset color
	@echo -n "$(PERCENT) $@"
	@printf "\e[0K\n\e[u\e[?25h"
	@mkdir $(OBJS_PATH) $(OBJS_FOLDERS_BIS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< -MMD

val: lldb
	valgrind --leak-check=full --track-origins=yes ./a.out 127.0.0.1 4248

valgrind: lldb
	valgrind --suppressions=.valgrind.supp --leak-check=full --track-origins=yes ./a.out

valsup: lldb
	valgrind --gen-suppressions=all --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out

lldb:
	gcc -ggdb3 src/*/*.c libft/src/*.c -I include -I libft/include -ltermcap

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)
	@rm -rf obj

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@rm -rf a.out
	@printf "\e[1;31m"	# set red color
	@echo "[ $(NAME)   ] deleted."
	@printf "\e[0m"		# reset color
	@rm -rf obj
	$(DEL_DSYMFILE)

#ifconfig en0 | grep 'inet ' | cut -d ' ' -f2
#RECUPERE L ADRESSE IP DE LA MACHINE
re: fclean all
