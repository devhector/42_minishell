NAME = minishell

LIBFT_PATH = ./libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

INCLUDE_PATH = includes

CC =	@clang-12
CFLAGS	= -Wall -Werror -Wextra -g

LFLAGS =	-lreadline -L $(LIBFT_PATH) -lft

CFLAGS += $(addprefix -I , $(INCLUDE_PATH))

vpath %.h $(INCLUDE_PATH)

vpath %.c	src src/hashTable src/env src/scan src/lexer src/syntax \
			src/execute src/command src/utils src/builtins

SRC =	main.c minishell.c hash_table.c hash_utils.c hash_env.c create_env.c \
		env_utils.c tokens_func.c scan.c check_char.c check_tokens.c lexer.c \
		syntax.c execute.c execute_utils.c command.c command_table.c expanse.c \
		free_utils.c here_doc.c clean_shell.c print_error.c bultins_utils.c \
		b_echo.c b_cd.c b_exit.c b_export.c b_env.c b_unset.c b_pwd.c expansor.c \
		checker.c utils.c fd_utils.c execute_signal.c signal.c


RM = @rm -rf

OBJ_DIR = obj

OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "Creating $(NAME)"
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) bonus

$(OBJ_DIR)/%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

v:	all
	@valgrind --suppressions=./r.supp --leak-check=full --track-origins=yes \
	--trace-children=yes --show-leak-kinds=all -q ./$(NAME)

r:	all
	clear
	./$(NAME)

debug: all
	@gdb $(NAME)

.PHONY: all clean fclean re
