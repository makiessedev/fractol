NAME=fractol
CC=cc
C_FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
C_FILES = fractol.c utils.c events.c
C_OBJ = $(C_FILES:.c=.o)

$(NAME): $(C_OBJ)
	$(CC) $(C_FLAGS) $(C_FILES) $(MLX_FLAGS) -o $(NAME)
all: $(NAME)

clean:
	${RM} ${C_OBJ}

fclean: clean
	$(RM) $(NAME)

re: clean all