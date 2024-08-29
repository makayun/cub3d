/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:42:48 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/29 00:40:31 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_background_draw(t_image *image, int *colors)
{
	float			gradient;
	unsigned int	color;
	const int		mid = WIN_HEIGHT >> 1;
	int				x;
	int				y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		gradient = fabs(((float)y + (-WIN_HEIGHT * (y <= mid))) / mid) / 2;
		color = cub_adjust_brightness(colors[y >= mid], gradient);
		x = 0;
		while (x < WIN_WIDTH)
		{
			cub_draw_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	cub_player_draw(t_data *data)
{
	t_coord	coordinates;
	t_coord	line_end;

	coordinates = cub_pos_to_coord(data->player->pos);
	line_end.x = coordinates.x + cos(data->player->angle) * POINTER_LENGHT;
	line_end.y = coordinates.y + sin(data->player->angle) * POINTER_LENGHT;
	cub_draw_line(data->render, coordinates, line_end, YELLOW);
	coordinates.x--;
	coordinates.y--;
	cub_draw_square(data->render, coordinates, 3, YELLOW);
}

void	cub_map_draw(t_data *data)
{
	unsigned int	i;
	const int		color[2] = {BLACK, GRAY};
	t_coord			coord;

	i = 0;
	while (i < data->map->size)
	{
		coord.x = (i % data->map->x) * BLOCK;
		coord.y = (i / data->map->x) * BLOCK;
		cub_draw_square(data->render, coord, BLOCK, color[data->map->map[i]]);
		i++;
	}
}

int	cub_render(t_data *data)
{
	const long	current_time = cub_current_time();

	if (current_time >= data->next_frame)
	{
		cub_movement_update(data);
		cub_background_draw(data->render, data->map->back_colors);
		cub_map_draw(data);
		cub_player_draw(data);
		cub_rays_n_walls(data->player, data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->render->img, 0, 0);
		data->next_frame = current_time + FRAME_TIME;
		return (ALL_FINE);
	}
	return (NOT_YET);
}
