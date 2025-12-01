# Variables
NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC	= 	\
		main.c \
		utils/lists/ft_lstadd_back.c \
		utils/lists/ft_lstclear.c \
		utils/lists/ft_lstdelone.c \
		utils/lists/ft_lstlast.c \
		utils/lists/ft_lstnew.c \

OBJ_DIR = objects
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT = libft/libft.a
MLX	= minilibx-linux/libmlx_Linux.a

MLX_INCLUDE = -I/usr/include -Iminilibx-linux -O3
MLX_LINK = -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm
MATH_LINK = -lm

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LINK) $(MATH_LINK) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(dir $(LIBFT))

$(MLX):
	make -C $(dir $(MLX))

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	make -C $(dir $(MLX)) clean
	make -C $(dir $(LIBFT)) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(dir $(LIBFT)) fclean
	rm -f $(NAME)

re: fclean all