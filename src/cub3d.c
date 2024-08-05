/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:15 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/05 01:28:05 by maxmakagono      ###   ########.fr       */
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

void	cub_turn(int side, t_player *player)
{
	if (side == LEFT)
	{
		player->angle -= (float)0.1;
		if (player->angle < 0)
			player->angle += 2 * M_PI;
	}
	else if (side == RIGHT)
	{
		player->angle += (float)0.1;
		if (player->angle > 2 * M_PI)
			player->angle -= 2 * M_PI;
	}
	player->delta.x = cos(player->angle) * STEP;
	player->delta.y = sin(player->angle) * STEP;
}

void	cub_step(int dir, t_player *player)
{
	player->pos.x += player->delta.x * (float)dir;
	player->pos.y += player->delta.y * (float)dir;
}

int	cub_key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cub_exit(data);
	else if (keysym == XK_d || keysym == XK_Right)
		cub_turn(RIGHT, data->player);
	else if (keysym == XK_a || keysym == XK_Left)
		cub_turn(LEFT, data->player);
	else if (keysym == XK_w || keysym == XK_Up)
		cub_step(FORWARD, data->player);
	else if (keysym == XK_s || keysym == XK_Down)
		cub_step(BACKWARD, data->player);
	else if (keysym == XK_equal)
		data->player->fow = ++data->player->fow - (data->player->fow > 60);
	else if (keysym == XK_minus)
		data->player->fow = --data->player->fow + (data->player->fow == 0);
	cub_draw(data);
	printf ("Angle: %f, x: %f, y: %f, FOW: %d\n", data->player->angle, data->player->pos.x, data->player->pos.y, data->player->fow);
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
	cub_draw(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &cub_key_handle, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &cub_exit, &data);
	mlx_loop(data.mlx);
}
