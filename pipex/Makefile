#colors
RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS =	main.c parse.c utils.c execute.c
OBJS = $(SRC:.c=.o)

INCLUDES_DIR = includes
LIBFT = $(INCLUDES_DIR)/libft.a
PRINTF = $(INCLUDES_DIR)/libftprintf.a

all: $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(PRINTF) -o $(NAME)
		@echo $(GREEN) " - Compilation FINISHED!" $(RESET)

clean:
		@rm -f $(OBJS)
		@echo $(RED) " - Cleaned!" $(RESET)
	
fclean: clean
		@rm -f $(NAME)
		@echo $(RED) " - Full Cleaned!" $(RESET)

re: fclean all

.PHONY: clean