/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:28:26 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/14 15:59:11 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_draw_square(t_image *image, t_coord coord, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			cub_draw_pixel(image, coord.x + j, coord.y + i, color);
			j++;
		}
		i++;
	}
}

void	cub_draw_line(t_image *image, t_coord start, t_coord end, int color)
{
	t_coord	dlt;
	t_coord	step;
	int		err;
	int		e2;

	dlt.x = abs(end.x - start.x);
	dlt.y = abs(end.y - start.y);
	step.x = 1 - 2 * (start.x > end.x);
	step.y = 1 - 2 * (start.y > end.y);
	err = (((dlt.x > dlt.y) * dlt.x) + ((dlt.y > dlt.x) * -dlt.y)) / 2;
	while (1)
	{
		cub_draw_pixel(image, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = err;
		err += (e2 > -dlt.x) * -dlt.y + (e2 < dlt.y) * dlt.x;
		start.x += (e2 > -dlt.x) * step.x;
		start.y += (e2 < dlt.y) * step.y;
	}
}

void	cub_draw_player(t_data *data)
{
	t_coord	coordinates;
	t_coord	line_end;

	coordinates.x = (int)data->player->pos.x - 1;
	coordinates.y = (int)data->player->pos.y - 1;
	cub_draw_square(data->render, coordinates, 3, YELLOW);
	coordinates = cub_pos_to_coord(data->player->pos);
	line_end.x = coordinates.x + cos(data->player->angle) * POINTER_LENGHT;
	line_end.y = coordinates.y + sin(data->player->angle) * POINTER_LENGHT;
	cub_draw_line(data->render, coordinates, line_end, YELLOW);
}

void	cub_draw_map(t_data *data)
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
	cub_draw_player(data);
}
