/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:10 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/23 15:17:02 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

	// MATH CONSTANTS
	// M_E       base of natural logarithm, e
	// M_LOG2E   log2(e)
	// M_LOG10E  log10(e)
	// M_LN2     ln(2)
	// M_LN10    ln(10)
	// M_PI      pi
	// M_PI_2    pi / 2
	// M_PI_4    pi / 4
	// M_1_PI    1 / pi
	// M_2_PI    2 / pi
	// M_2_SQRTPI 2 / sqrt(pi)
	// M_SQRT2   sqrt(2)
	// M_SQRT1_2 sqrt(1/2)

# define DEG_TO_RAD 0.0174533
# define PI_TWICE	6.28318530718

# define WEST		3.141593
# define EAST		0.0
# define NORTH		4.712389
# define SOUTH		1.570796

# define CUB_ERROR -1
# define NOT_YET	0
# define ALL_FINE	1

# define CEILING	0
# define FLOOR		1
# define HOR		0
# define VERT		1

# define WIN_WIDTH	1024
# define WIN_HEIGHT	640

# define BLOCK		16

enum e_map_constants
{
	MAP_WIDTH_MAX =		WIN_WIDTH/BLOCK,
	MAP_HEIGHT_MAX =	WIN_HEIGHT/BLOCK,
	MAP_MAX =			MAP_WIDTH_MAX*MAP_HEIGHT_MAX,
	WALL_Y_Q =			WIN_HEIGHT*BLOCK/2*3,
	STEP =				BLOCK/8,
	POINTER_LENGHT =	BLOCK/2,
	HITBOX_LIMIT =		STEP * 2,
};

enum e_fps
{
	FPS =			30,
	FRAME_TIME =	1000000 / FPS,
};

# define FOW_MAX	120
# define FOW_MIN	4

# define RES_MAX	WIN_WIDTH
# define RES_MIN	4

# define BLACK		0x0
# define GRAY		0x00C0C0C0
# define WHITE		0x00FFFFFF
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF
# define YELLOW		0x00FFFF00

# define ANSI_DEF		"\001\e[0m\002"
# define ANSI_GRAY		"\001\e[0;90m\002"
# define ANSI_RED		"\001\e[0;91m\002"
# define ANSI_GREEN		"\001\e[0;92m\002"
# define ANSI_MAGENTA	"\001\e[35m\002"
# define ANSI_CYAN		"\001\e[36m\002"

# define FORWARD	1
# define BACKWARD  -1
# define RIGHT		1
# define LEFT	   -1

enum e_keys
{
	KEY_LA,
	KEY_RA,
	KEY_W,
	KEY_S,
	KEY_D,
	KEY_A,
};

typedef struct s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct s_position
{
	float			x;
	float			y;
}				t_pos;

typedef struct s_map
{
	bool			map[MAP_MAX];
	int				back_colors[2];
	int	x;
	int	y;
	unsigned int	size;
	unsigned int	shift;
	int	w;
	int	h;
	bool			draw_rays;
}				t_map;

typedef struct s_ray
{
	t_pos			hit_pos[2];
	t_pos			pos;
	float			dist[2];
	float			angle;
	int			num;
	bool			hit;
}				t_ray;

typedef struct s_player
{
	t_pos			pos;
	t_pos			delta;
	float			angle;
	int			fow;
	int			res;
}				t_player;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}				t_image;

enum e_textures
{
	WALL_WEST,
	WALL_EAST,
	WALL_NORTH,
	WALL_SOUTH,
};

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_image			*render;
	t_player		*player;
	t_map			*map;
	t_image			*texture;
	long			next_frame;
	bool			keys[6];
}				t_data;

long	cub_current_time(void);
int		cub_check_input(int argc, char *filename);
int		cub_exit(t_data *data);

void	cub_init(char **argv, t_data *data);
int		cub_parse(char **argv, t_data *data);
void	cub_init_map(t_data *data);
void	cub_init_player(t_data *data);
void	cub_init_images(t_data *data);

int		cub_key_press(int keysym, t_data *data);
void	cub_key_hold(int keysym, t_data *data);
int		cub_key_release(int keysym, t_data *data);

void	cub_movement_update(t_data *data);
void	cub_turn(int side, float turn_angle, t_player *player);
void	cub_step(int dir, t_data *data);
void	cub_slide(int dir, t_data *data);

int		cub_render(t_data *data);
void	cub_draw_pixel(t_image *img, int x, int y, unsigned int color);
void	cub_draw_map(t_data *data);
void	cub_draw_line(t_image *image, t_coord start, t_coord end, int color);

void	cub_rays_n_walls(t_player *player, t_map *map, t_data *data);
float	cub_dist(t_pos a, t_pos b);
void	cub_walls_draw(t_data *data, t_ray *ray, float dist);

int		cub_adjust_brightness(int color, float factor);
float	cub_fisheye(t_data *data, float ray_angle, float ray_dist);
float	cub_gradient(float frow);
t_coord	cub_pos_to_coord(t_pos pos);
void	cub_tool_coord_norm(int *x, int *y);

int		cub_walls_draw_texture(t_data *data, t_ray *ray, float *pos, float dist);
void	cub_slice(t_data *data, t_ray *ray, float *pos, float dist);
#endif