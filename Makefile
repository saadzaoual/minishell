#colors
RESET       = "\033[0m"
RED         = "\033[31m"
GREEN       = "\033[32m"
YELLOW      = "\033[33m"
#colors

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	minishell.c \
		src/parser/token.c \
		src/parser/parcer.c \
		src/execution/builtins/builtins.c \
		src/execution/builtins/cd.c \
		src/execution/builtins/echo.c \
		src/execution/builtins/env.c \
		src/execution/builtins/exit.c \
		src/execution/builtins/export.c \
		src/execution/builtins/pwd.c \
		src/execution/builtins/unset.c \
		src/execution/excve/path.c \
		src/execution/excve/execute.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -L$(LIBFT_DIR) -lft
INCLUDES = -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
	@echo $(GREEN) " - Compiling FINISHED" $(RESET)


$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -Iincludes -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo $(RED) " - Cleaned!" $(RESET)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo $(RED) " - Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re

