/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:15 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/08 11:24:41 by maxmakagono      ###   ########.fr       */
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

int	cub_key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cub_exit(data);
	else if (keysym == XK_Right)
		cub_turn(RIGHT, 0.1, data->player);
	else if (keysym == XK_Left)
		cub_turn(LEFT, 0.1, data->player);
	else if (keysym == XK_w || keysym == XK_Up)
		cub_step(FORWARD, data->player);
	else if (keysym == XK_s || keysym == XK_Down)
		cub_step(BACKWARD, data->player);
	else if (keysym == XK_a)
		cub_slide(LEFT, data->player);
	else if (keysym == XK_d)
		cub_slide(RIGHT, data->player);
	else if (keysym == XK_equal)
		data->player->fow = ++data->player->fow - (data->player->fow > FOW_MAX);
	else if (keysym == XK_minus)
		data->player->fow = --data->player->fow + (data->player->fow < FOW_MIN);
	else if (keysym == XK_p)
		data->player->res *= 1 + (data->player->res < RES_MAX);
	else if (keysym == XK_o)
		data->player->res /= 1 + (data->player->res > RES_MIN);
	cub_render(data);
	printf ("Angle: %f, x: %f, y: %f, FOW: %d, res: %d\n", data->player->angle, data->player->pos.x, data->player->pos.y, data->player->fow, data->player->res);
	return (ALL_FINE);
}

int	main()
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
	mlx_hook(data.win, KeyPress, KeyPressMask, &cub_key_handle, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &cub_exit, &data);
	mlx_loop(data.mlx);
}
