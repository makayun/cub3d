/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:10 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/07 10:04:14 by maxmakagono      ###   ########.fr       */
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
# define PI_TWICE	M_PI*2

# define WIN_WIDTH 1440
# define WIN_HEIGHT 900

# define FT_ERROR	-1
# define ALL_FINE	1
# define CEILING	0
# define FLOOR		1
# define HOR		0
# define VERT		1

# define MAP_BLOCK		16
# define MAP_WIDTH_MAX	WIN_WIDTH/MAP_BLOCK
# define MAP_HEIGHT_MAX	WIN_HEIGHT/MAP_BLOCK
# define MAP_MAX		MAP_WIDTH_MAX*MAP_HEIGHT_MAX
# define STEP			MAP_BLOCK/4
# define POINTER_LENGHT	MAP_BLOCK/2

# define FOW_MAX	120
# define FOW_MIN	4

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
# define BACKWARD	-1
# define RIGHT		2
# define LEFT		-2	

typedef struct s_coord {
	short	x;
	short	y;
}				t_coord;

typedef struct s_position {
	float	x;
	float	y;
}				t_position;

typedef struct s_map {
	bool			map[MAP_MAX];
	unsigned int	x;
	unsigned int	y;
	unsigned int	size;
	unsigned int	shift;
}				t_map;

typedef struct s_ray {
	t_position	hit[2];
	t_position	pos;
	float		dist[2];
	float		angle;
	int			num;
	bool		vert_hit;
}				t_ray;

typedef struct s_player {
	t_position		pos;
	t_position		delta;
	float			angle;
	int				fow;
}				t_player;

typedef struct s_image {
    void	*img;
    char	*addr;
	int		back_colors[2];
    int		bpp;
    int		line_len;
    int		endian;
}				t_image;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_image		*render;
	t_player	*player;
	t_map		*map;
}				t_data;

void	cub_init(t_data *data);
void	cub_draw(t_data *data);
void	cub_draw_pixel(t_image *img, short x, short y, unsigned int color);
void	cub_draw_map(t_data *data);
void	cub_draw_line(t_image *image, t_coord start, t_coord end, int color);
void	cub_rays(t_player *player, t_map *map, t_image *image, t_data *data);
t_coord	cub_pos_to_coord(t_position pos);
void	cub_tool_coord_norm(short *x, short *y);
float	cub_dist(t_position a, t_position b);

unsigned int	cub_adjust_brightness(int color, float factor);
float			cub_gradient(float frow);

#endif