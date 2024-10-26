NAME=fractol
CC=cc
C_FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -lXext -lX11 -lm -lz
C_FILES = fractol.c utils.c fractol_utils.c atoid.c
C_OBJ = $(C_FILES:.c=.o)

$(NAME): $(C_OBJ)
	make -C ./minilibx-linux
	$(CC) $(C_FLAGS) $(C_FILES) $(MLX_FLAGS) -o $(NAME)
all: $(NAME)

clean:
	${RM} ${C_OBJ}

fclean: clean
	$(RM) $(NAME)

re: clean all
