NAME = builtins

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft.h

SRCS = builtins.c echo.c cd.c\
		exit.c pwd.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean