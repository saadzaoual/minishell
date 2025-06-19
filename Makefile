NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = minishell.c \
              src/parser/token.c \
              src/parser/parcer.c \
			  src/parser/syntax_error.c \
              src/utils/token_utils/token1_utils.c \
              src/utils/token_utils/token2_utils.c \
              src/utils/parcer_utils/parcer1_utils.c

OBJS        = $(SRCS:.c=.o)

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

INCLUDES    = -I$(LIBFT_DIR)
LIBS        = -lreadline -L$(LIBFT_DIR) -lft

YELLOW      = \033[1;33m
GREEN       = \033[1;32m
BLUE        = \033[1;34m
RESET       = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)[LINK]$(RESET)     Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)[DONE]$(RESET)     Executable built!"

$(LIBFT):
	@echo "$(YELLOW)[LIBFT]$(RESET)    Building Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

%.o: %.c
	@echo "$(BLUE)[COMPILE]$(RESET)  $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)[CLEAN]$(RESET)   Removing object files..."
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)[FCLEAN]$(RESET)  Removing executable and libft..."
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all
.PHONY: all clean fclean re