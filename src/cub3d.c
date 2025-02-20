/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:15 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/30 15:41:07 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4 && data->texture[i].img != NULL)
		mlx_destroy_image(data->mlx, data->texture[i++].img);
	mlx_destroy_image(data->mlx, data->render->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free (data->mlx);
	exit(data->exit_code);
	return (42);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_player	player;
	t_image		render;
	t_image		textures[4];
	t_map		map;

	if (cub_check_input(argc, argv[1]) == CUB_ERROR)
		return (EXIT_FAILURE);
	data.player = &player;
	data.render = &render;
	data.map = &map;
	data.texture = textures;
	cub_init(argv, &data);
	data.next_frame = cub_current_time();
	cub_render(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &cub_key_press, &data);
	mlx_key_hook(data.win, &cub_key_release, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &cub_exit, &data);
	mlx_loop_hook(data.mlx, &cub_render, &data);
	mlx_loop(data.mlx);
}
