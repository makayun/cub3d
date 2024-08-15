/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:41:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/14 10:53:29 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_mlx(t_data *data)
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
}

void	cub_init(char  **argv, t_data *data)
{
	int i;

	cub_parse(argv, data);
	cub_init_mlx(data);
	i = 0;
	while (i < 6)
		data->keys[i++] = 0;
	cub_init_map(data);
	cub_init_images(data);
	cub_init_player(data);
}
