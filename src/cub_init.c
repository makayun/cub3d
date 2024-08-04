/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:41:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/04 11:27:23 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_map(t_data *data)
{
	unsigned int		i;
	bool  test_map[] = {1, 1, 1, 1, 1, 1, 1, 1,
						1, 0, 1, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 1, 0, 1,
						1, 0, 0, 0, 0, 1, 0, 1,
						1, 1, 1, 1, 1, 1, 1, 1 };
	data->map->size = 64;
	data->map->x = 8;
	data->map->y = 8;
	i = -1;
	while (++i < data->map->size)
		data->map->map[i] = test_map[i];

}

void	cub_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit (EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "let's fly!");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit (EXIT_FAILURE);
	}
	data->render->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->render->addr = mlx_get_data_addr(data->render->img, &data->render->bpp, &data->render->line_len, &data->render->endian);
	data->player->pos.x = 40;
	data->player->pos.y = 40;
	data->player->angle = 0;
	data->player->delta.x = cos(data->player->angle) * STEP;
	data->player->delta.y = sin(data->player->angle) * STEP;
	data->render->back_colors[FLOOR] = BLUE;
	data->render->back_colors[CEILING] = GREEN;
	cub_init_map(data);
}
