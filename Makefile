NAME = minishell

LIBFT_PATH = ./libraries/libft
LIBFT = $(LIBFT_PATH)/libft.a

CC =	gcc
CFLAGS	= -Wall	\
		-Werror	\
		-Wextra

LFLAGS =	-lreadline		\
			-L				\
			$(LIBFT_PATH)	\
			-lft

vpath %.c src			\
		src/input		\

# src/builtin		\
# src/parser		\
# src/signal		\

SRC =	main.c				\
		minishell.c			\
		next_char.c			\
		peak_char.c			\
		skip_white_space.c	\
		unget_char.c

RM = rm -rf

OBJ_DIR = obj

OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

v:	all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

r:	all
	clear
	./$(NAME)

.PHONY: all clean fclean re
