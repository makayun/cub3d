/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:28:26 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/06 00:19:45 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static inline void	cub_draw_square(t_image *image, t_coord coord, int size, int color)
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

void cub_draw_line(t_image *image, t_coord start, t_coord end, int color)
{
	t_coord	delta;
	t_coord	step;
	int		sign[2];
    int		err;
    int		e2;

	end.x *= (end.x > 0);
	end.y *= (end.y > 0);
	end.x += (end.x > WIN_WIDTH) * (WIN_WIDTH - end.x - 1);
	end.y += (end.y > WIN_HEIGHT) * (WIN_HEIGHT - end.y - 1);
	sign[0] = -1;
	sign[1] = 1;
	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	step.x = sign[start.x < end.x];
	step.y = sign[start.y < end.y];
    if (delta.x > delta.y)
        err = delta.x / 2;
    else
        err = -delta.y / 2;
    while (1)
    {
        cub_draw_pixel(image, start.x, start.y, color);
        if (start.x == end.x && start.y == end.y)
            break;
        e2 = err;
        if (e2 > -delta.x)
        {
            err -= delta.y;
            start.x += step.x;
        }
        if (e2 < delta.y)
        {
            err += delta.x;
            start.y += step.y;
        }
    }
}

void	cub_draw_player(t_data *data)
{
	t_coord	coordinates;
	t_coord line_end;

	coordinates.x = (int)data->player->pos.x - MAP_BLOCK / 8;
	coordinates.y = (int)data->player->pos.y - MAP_BLOCK / 8;
	cub_draw_square(data->render, coordinates, MAP_BLOCK / 4, YELLOW);
	cub_rays(data->player, data->map, data->render);
	coordinates = cub_pos_to_coord(data->player->pos);
	line_end.x = coordinates.x + cos(data->player->angle) * POINTER_LENGHT;
	line_end.y = coordinates.y + sin(data->player->angle) * POINTER_LENGHT;
	cub_draw_line(data->render, coordinates, line_end, YELLOW);
}

void	cub_draw_map(t_data *data)
{
	unsigned int	i;
	int				color[2];
	t_coord			coord;
	
	color[0] = BLACK;
	color[1] = GRAY;
	i = 0;
	while (i < data->map->size)
	{
		coord.x = (i % data->map->x) * MAP_BLOCK;
		coord.y = (i / data->map->x) * MAP_BLOCK;
		cub_draw_square(data->render, coord, MAP_BLOCK, color[data->map->map[i]]);
		i++;
	}
	cub_draw_player(data);
	
}
