
.PHONY: all, clean, fclean, re.
NAME = wolf3d

LIBFT_PATH = libft/
MLX_PATH = -L  /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

INC = -I ./include/ -I ./$(LIBFT_PATH)include/ -I /usr/local/include/

SRCS_NAME =  src/draw.c \
             src/draw2.c \
             src/init.c \
             src/main.c \
             src/key_events.c \
             src/read.c \
             src/read2.c \
             src/texture.c

SRCO_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(SRCS_NAME) $(INC) -L $(LIBFT_PATH) -lft $(MLX_PATH) -o $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all