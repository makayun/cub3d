/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:15 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/12 08:36:44 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->render->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free (data->mlx);
	exit(EXIT_SUCCESS);
	return (42);
}

int	main(void)
{
	t_data		data;
	t_player	player;
	t_image		render;
	t_map		map;

	data.player = &player;
	data.render = &render;
	data.map = &map;
	cub_init(&data);
	cub_render(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &cub_key_press, &data);
	mlx_key_hook(data.win, &cub_key_release, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &cub_exit, &data);
	mlx_loop(data.mlx);
}
