/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:41:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/06 11:06:30 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_count_shift(void)
{
    int shift;
    int	map_block;

    map_block = MAP_BLOCK;
    shift = 1;
    while (1)
    {
        map_block = map_block >> 1;
        if (map_block == 1)
            return (shift);
        shift++;
    }
}

void	cub_init_map(t_data *data)
{
	unsigned int		i;
	bool  test_map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
						1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
						1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
						1, 0, 1, 0, 1, 0, 0, 1, 0, 1,
						1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	data->map->size = 100;
	data->map->x = 10;
	data->map->y = 10;
	data->map->shift = cub_count_shift();
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
	data->player->pos.x = 50;
	data->player->pos.y = 40;
	data->player->angle = 3 * M_PI_2;
	data->player->delta.x = cos(data->player->angle) * STEP;
	data->player->delta.y = sin(data->player->angle) * STEP;
	data->player->fow = FOW_MAX / 2;
	data->render->back_colors[FLOOR] = MAGENTA;
	data->render->back_colors[CEILING] = GRAY;
	cub_init_map(data);
}
