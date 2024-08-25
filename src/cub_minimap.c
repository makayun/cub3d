/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:28:26 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/25 22:07:27 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_player_draw(t_data *data)
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
	cub_player_draw(data);
}
