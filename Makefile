.PHONY: all clean fclean re

NAME = taskmaster
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft
INC = -I libft/ft_printf/srcs/ -I libft/get_next_line -I libft/srcs
SRCS_PATH = srcs
OBJS_PATH = objs
CLIENT_PATH = client
CLIENT = cl_taskmaster

SRCS_NAME =	ft_main.c			\
			ft_exec_jobs.c		\
			ft_commands.c		\
			ft_status.c			\
			ft_parse_config.c	\
			ft_utils.c			\
			ft_memory_utils.c	\
			ft_jobs_funcs.c		\
			ft_parse_utils.c	\
			ft_server_loop.c	\
			the_bazard.c		\
			ft_server_utils.c

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS = $(addprefix $(OBJS_PATH)/,$(OBJS_NAME))
SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))
NB_FILES = $(words $(SRCS_NAME))

all: $(NAME)

$(NAME): $(CLIENT_PATH)/$(CLIENT) $(LIBFT)/libft.a $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft
	@(printf "\033[1A" && printf "\033[K") # remove last line
	@echo "\033[92mCOMPILED:  taskmaster\033[0m [100%]"
	@echo "\033[93m>> taskmaster is ready <<\033[0m"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(SRCS_PATH)/taskmaster.h
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@(printf "\033[1A" && printf "\033[K") # remove last line
	@echo "\033[93mCOMPILING: taskmaster\033[0m [$(PERCENT)%]"
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<


val:
	$(CC) -g $(FLAGS) $(TERMFLAGS) srcs/*.c $(INC) libft/srcs/*.c libft/ft_printf/srcs/*.c libft/get_next_line/*.c
	valgrind --leak-check=full --track-origins=yes ./a.out configs/lol.geo

sanitize:
	$(CC) $(FLAGS) fsanitize=address srcs/*.c $(INC) libft/srcs/*.c libft/ft_printf/srcs/*.c
	a.out -lR /

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(CLIENT_PATH)/$(CLIENT):
	@make -C $(CLIENT_PATH)

clean:
	@(cd $(LIBFT) && make clean)
	@(cd $(CLIENT_PATH) && make clean)
	@rm -rf srcs/list_dir_content.o
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -rf $(NAME)
	@(cd $(LIBFT) && make fclean)
	@(cd $(CLIENT_PATH) && make fclean)

re: fclean all
