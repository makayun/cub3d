/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:10 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/03 04:21:35 by maxmakagono      ###   ########.fr       */
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

# define WIN_WIDTH 1024
# define WIN_HEIGHT 640

# define FT_ERROR	-1
# define ALL_FINE	1
# define FLOOR		1
# define CEILING	0

# define MAP_MAX 64*64
# define MAP_BLOCK 16

# define BLACK		0x0
# define GRAY		0x00C0C0C0
# define WHITE		0x00FFFFFF
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF
# define YELLOW		0x00FFFF00

typedef struct s_coord {
	int	x;
	int	y;
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
}				t_map;

typedef struct s_player {
	t_position		pos;
	int				dir;
}				t_player;

typedef struct s_image
{
    void	*img;
    char	*addr;
	int		back_colors[2];
    int		bpp;
    int		line_len;
    int		endian;
}	t_image;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_image		render;
	t_player	player;
	t_map		map;
}				t_data;

void	cub_init(t_data *data);
void	cub_draw(t_data *data);
void	cub_draw_pixel(t_image *img, int x, int y, unsigned int color);
void	cub_draw_map(t_data *data);

unsigned int	cub_adjust_brightness(int color, float factor);
float			cub_gradient(float frow);

#endif