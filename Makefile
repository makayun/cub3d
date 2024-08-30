NAME = cub3D
UNAME = $(shell uname -s)
CC = @clang
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
HEADERS = ./cub3d.h
RM = @rm -rf

ifeq ($(UNAME),Darwin)
MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework AppKit -I/opt/X11/include -L/usr/X11/lib -lXext -lX11 -L./libft -lft
INCLUDES = -I/opt/X11/include -Imlx -Ilibft
else
MLX_FLAGS = -L./mlx -lmlx -lX11 -lXext -lm -L./libft -lft
INCLUDES = -I/usr/include -Imlx -Ilibft
endif

FILES = cub3d \
		cub_checks \
		cub_draw \
		cub_init \
		cub_keys \
		cub_movements \
		cub_parse \
		cub_rays \
		cub_render \
		cub_tools_graphics \
		cub_tools \
		cub_walls

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
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

norm: $(NAME)
	@norminette $(SRCS) $(HEADERS)

.PHONY: all clean fclean re fre norm