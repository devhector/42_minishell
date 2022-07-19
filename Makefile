NAME = minishell

LIBFT_PATH = ./libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

INCLUDE_PATH = includes

CC =	@gcc
CFLAGS	= -Wall -Werror -Wextra -g

LFLAGS =	-lreadline -L $(LIBFT_PATH) -lft

CFLAGS += $(addprefix -I , $(INCLUDE_PATH))

vpath %.h $(INCLUDE_PATH)

vpath %.c src src/hashTable src/env src/scan \

# src/builtin		\
# src/parser		\
# src/signal		\

SRC =	main.c minishell.c hash_table.c hash_utils.c create_env.c \
		tokens_func.c scan.c check_char.c check_tokens.c \
		 


RM = @rm -rf

OBJ_DIR = obj

OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "Creating $(NAME)"
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

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
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--suppressions=readline.supp --trace-children=yes --verbose \
	--log-file=valgrind-out.txt ./$(NAME)

r:	all
	clear
	./$(NAME)

debug: all
	@gdb $(NAME)

.PHONY: all clean fclean re
