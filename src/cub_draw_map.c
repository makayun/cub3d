/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:28:26 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/03 09:08:01 by maxmakagono      ###   ########.fr       */
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

void	cub_draw_player(t_data *data)
{
	t_coord	coordinates;

	coordinates.x = data->player.pos.x;
	coordinates.y = data->player.pos.y;
	cub_draw_square(&data->render, coordinates, MAP_BLOCK / 4, YELLOW);
}

void	cub_draw_map(t_data *data)
{
	unsigned int	i;
	int				color[2];
	t_coord			coord;
	
	color[0] = BLACK;
	color[1] = GRAY;
	i = 0;
	while (i < data->map.size)
	{
		coord.x = (i % data->map.x) * MAP_BLOCK;
		coord.y = (i / data->map.x) * MAP_BLOCK;
		cub_draw_square(&data->render, coord, MAP_BLOCK, color[data->map.map[i]]);
		i++;
	}
	cub_draw_player(data);
}

// 0123 4567 890a bcde

// 1111 1111 1010 0001
// 0000 0000 0000 0000



