NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = 	./src/main.c \
		./src/tokenize/token.c \
		./src/tokenize/validate.c \
		./src/tokenize/syntax.c \
		./src/tokenize/together.c\
		./src/redirect/heredoc.c\
		./src/utils/printer.c \
		./src/ast/ast.c \
		./src/builtin/echo.c \
		./src/builtin/envp_shellzito.c \
		./src/builtin/export.c \

OBJ_DIR = obj

OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS	= -I ./include -I $(LIBFT_PATH)/include

OK_COLOR    = \033[0;32m

all: intro $(NAME)

intro:
	@printf "%b" "$(OK_COLOR)"
	@echo "                #             #           #              ##     ##    "
	@echo "                                          #               #      #    "
	@echo "       ## #    ##    # ##    ##     ###   # ##    ###     #      #    "
	@echo "       # # #    #    ##  #    #    #      ##  #  #   #    #      #    "
	@echo "       # # #    #    #   #    #     ###   #   #  #####    #      #    "
	@echo "       # # #    #    #   #    #        #  #   #  #        #      #    "
	@echo "       #   #   ###   #   #   ###   ####   #   #   ###    ###    ###   "

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@ -g3 $(HEADERS)
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -g3 $(OBJ) $(HEADERS) $(LIBFT) -o $(NAME) -lreadline
	@echo "Compilation complete!"

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "Cleaning completed!"

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -q --track-origins=yes --track-fds=yes --trace-children-skip='*/bin/*,*/sbin/*' --suppressions=readline.supp ./$(NAME)

re: fclean all

.PHONY: all clean fclean re