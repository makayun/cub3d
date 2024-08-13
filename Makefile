NAME = cub3d
UNAME = $(shell uname -s)
CC = @clang
CFLAGS = -Wall -Wextra -Werror -Ofast -g -fsanitize=address
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = @rm -rf

ifeq ($(UNAME),Darwin)
MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework AppKit -I/opt/X11/include -L/usr/X11/lib -lXext -lX11 -L./libft -lft
INCLUDES = -I/opt/X11/include -Imlx -Ilibft
else
MLX_FLAGS = -L./mlx -lmlx -lX11 -lXext -lm -L./libft -lft
INCLUDES = -I/usr/include -Imlx -Ilibft
endif

SRCS_DIR = ./src/
SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c)

OBJS_DIR = ./obj/
OBJS = $(addprefix obj/,$(notdir $(SRCS:.c=.o)))
# OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

all: $(NAME)

$(NAME): ./cub3d.h $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
	@echo "Game compiled"

$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)

$(MLX_LIB):
	@make --quiet -C $(MLX_DIR)

clean:
	$(RM) $(OBJS_DIR) $(NAME)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

re: clean $(NAME)

fre: fclean $(NAME)

.PHONY: all clean fclean re fre