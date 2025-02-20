/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:10 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/09/02 09:52:52 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIN_WIDTH	1024
# define WIN_HEIGHT	640

# define BLOCK		16

enum e_map_constants
{
	MAP_W_MAX =		WIN_WIDTH/BLOCK,
	MAP_H_MAX =	WIN_HEIGHT/BLOCK,
	MAP_MAX =			MAP_W_MAX*MAP_H_MAX,
	WALL_Y_Q =			WIN_HEIGHT*BLOCK/2*3,
	STEP =				BLOCK/8,
	POINTER_LENGHT =	BLOCK/2,
	HITBOX_LIMIT =		STEP * 2,
};

enum e_fps
{
	FPS =			60,
	FRAME_TIME =	1000000 / FPS,
};

# define FOW_MAX	140
# define FOW_MIN	4

# define RES_MAX	WIN_WIDTH
# define RES_MIN	4

# define DEG_TO_RAD 0.0174533
# define PI_TWICE	6.28318530718

# define WEST		3.141593
# define EAST		0.0
# define NORTH		4.712389
# define SOUTH		1.570796

enum e_textures
{
	WALL_WEST,
	WALL_EAST,
	WALL_NORTH,
	WALL_SOUTH,
};

# define CUB_ERROR -1
# define NOT_YET	0
# define ALL_FINE	1

# define CEILING	0
# define FLOOR		1
# define HOR		0
# define VERT		1

# define FORWARD	1
# define BACKWARD  -1
# define RIGHT		1
# define LEFT	   -1

# define BLACK		0x0
# define GRAY		0x00C0C0C0
# define WHITE		0x00FFFFFF
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF
# define YELLOW		0x00FFFF00

# define T_DEF		"\001\e[0m\002"
# define T_GRAY		"\001\e[0;90m\002"
# define T_RED		"\001\e[0;91m\002"
# define T_GREEN	"\001\e[0;92m\002"
# define T_MAGENTA	"\001\e[35m\002"
# define T_CYAN		"\001\e[36m\002"

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
	int				x;
	int				y;
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
	unsigned int	x;
	unsigned int	y;
	unsigned int	size;
	unsigned int	shift;
	int				w;
	int				h;
	bool			draw_rays;
}				t_map;

typedef struct s_ray
{
	t_pos			hit_pos[2];
	t_pos			pos;
	float			dist[2];
	float			angle;
	int				num;
	bool			hit;
}				t_ray;

typedef struct s_player
{
	t_pos			pos;
	t_pos			delta;
	float			angle;
	int				fow;
	int				res;
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

typedef struct s_slice
{
	int				w_side;
	int				clmn;
	float			y_q;
	float			factor;
}				t_slice;

typedef struct s_data
{
	char			txtr_flnm[4][FILENAME_MAX];
	void			*mlx;
	void			*win;
	t_image			*render;
	t_player		*player;
	t_map			*map;
	t_image			*texture;
	long			next_frame;
	int				exit_code;
	bool			keys[6];
}				t_data;

long	cub_current_time(void);
int		cub_check_input(int argc, char *filename);
int		cub_check_map(char map[MAP_H_MAX][MAP_W_MAX], t_data *data);
int		cub_exit(t_data *data);

void	cub_init(char **argv, t_data *data);
int		cub_parse(char *filename, t_data *data);
int		cub_init_map(t_data *data, bool *map, char tmp[MAP_H_MAX][MAP_W_MAX]);
void	cub_init_images(t_data *data, t_image *render, t_image *texture);

int		cub_key_press(int keysym, t_data *data);
void	cub_key_hold(int keysym, t_data *data);
int		cub_key_release(int keysym, t_data *data);

void	cub_movement_update(t_data *data);
void	cub_turn(int side, float turn_angle, t_player *player);
void	cub_step(int dir, t_data *data);
void	cub_slide(int dir, t_data *data);

int		cub_render(t_data *data);
void	cub_draw_pixel(t_image *img, int x, int y, unsigned int color);
void	cub_draw_square(t_image *image, t_coord coord, int size, int color);
void	cub_map_draw(t_data *data);
void	cub_draw_line(t_image *image, t_coord start, t_coord end, int color);

void	cub_rays_n_walls(t_player *player, t_map *map, t_data *data);
float	cub_dist(t_pos a, t_pos b);
void	cub_walls_draw(t_data *data, t_ray *ray, float dist);

int		cub_adjust_brightness(int color, float factor);
float	cub_tool_fisheye(t_data *data, float ray_angle, float ray_dist);
float	cub_gradient(float frow);
t_coord	cub_pos_to_coord(t_pos pos);
void	cub_tool_coord_norm(int *x, int *y);
char	*cub_cut_whitespace(char *line);

void	cub_wall_slice(t_data *data, t_ray *ray, float *pos, float dist);
int		cub_get_pixel(t_image *img, int x, int y);
int		cub_w_side(t_ray *ray);
int		cub_get_column(int w_side, float ray_hit_pos, int img_side);
#endif