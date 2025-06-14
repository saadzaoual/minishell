#colors
RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32"

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c parse.c utils.c execute.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@$echo $(GREEN) " - Compilation FINISHED!" $(RESET)

clean:
		@rm -f $(OBJS)
		@echo $(RED) " - Cleaned!" $(RESET)
	
fclean: clean
		@rm -f $(NAME)
		@echo $(RED) " - Full Cleaned!" $(RESET)

re: fclean al;

.PHONY: clean