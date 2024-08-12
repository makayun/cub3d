/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:23:40 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/12 22:36:00 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_turn(int side, float turn_angle, t_player *player)
{
	player->angle += turn_angle * side;
	if (side == LEFT)
		player->angle += (player->angle < 0) * PI_TWICE;
	else if (side == RIGHT)
		player->angle -= (player->angle > PI_TWICE) * PI_TWICE;
	player->delta.x = cos(player->angle) * STEP;
	player->delta.y = sin(player->angle) * STEP;
}

// void	cub_step(int dir, t_data *data)
// {
// 	data->player->pos.x += data->player->delta.x * (float)dir;
// 	data->player->pos.y += data->player->delta.y * (float)dir;
// }

void	cub_step(int dir, t_data *data)
{
	t_pos	new_pos;
	t_coord	m;

	new_pos = data->player->pos;
	new_pos.x += data->player->delta.x * (float)dir * 3;
	m.x = (int)new_pos.x / BLOCK;
	m.y = (int)data->player->pos.y / BLOCK;
	if (data->map->map[m.y * data->map->x + m.x] == 0)
		data->player->pos.x += data->player->delta.x * (float)dir;
	new_pos = data->player->pos;
	new_pos.y += data->player->delta.y * (float)dir * 3;
	m.y = (int)new_pos.y / BLOCK;
	m.x = (int)data->player->pos.x / BLOCK;
	if (data->map->map[m.y * data->map->x + m.x] == 0)
		data->player->pos.y += data->player->delta.y * (float)dir;
}

void	cub_slide(int dir, t_data *data)
{
	cub_turn(dir, M_PI_2, data->player);
	cub_step(FORWARD, data);
	cub_turn(-dir, M_PI_2, data->player);
}

void	cub_movement_update(t_data *data)
{
	if (data->keys[KEY_RA])
		cub_turn(RIGHT, 0.1F, data->player);
	if (data->keys[KEY_LA])
		cub_turn(LEFT, 0.1F, data->player);
	if (data->keys[KEY_W])
		cub_step(FORWARD, data);
	if (data->keys[KEY_S])
		cub_step(BACKWARD, data);
	if (data->keys[KEY_D])
		cub_slide(RIGHT, data);
	if (data->keys[KEY_A])
		cub_slide(LEFT, data);
}
