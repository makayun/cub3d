/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:42:48 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/25 22:08:16 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_draw_background(t_image *image, int *colors)
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

int	cub_render(t_data *data)
{
	const long	current_time = cub_current_time();

	if (current_time >= data->next_frame)
	{
		cub_movement_update(data);
		cub_draw_background(data->render, data->map->back_colors);
		cub_map_draw(data);
		cub_rays_n_walls(data->player, data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->render->img, 0, 0);
		data->next_frame = current_time + FRAME_TIME;
		return (ALL_FINE);
	}
	return (NOT_YET);
}
