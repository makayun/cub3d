/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:23:40 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/25 00:49:16 by maxmakagono      ###   ########.fr       */
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

bool	cub_collision(t_data *data, float pos_x, float pos_y)
{
	t_coord		m;
	t_pos		offset;

	offset.y = -HITBOX_LIMIT;
	while (offset.y <= HITBOX_LIMIT)
	{
		m.y = (int)((pos_y + offset.y) / BLOCK);
		offset.x = -HITBOX_LIMIT;
		if (m.y < 0 || m.y >= (int)data->map->y)
			return (1);
		while (offset.x <= HITBOX_LIMIT)
		{
			m.x = (int)((pos_x + offset.x) / BLOCK);
			if (m.x < 0 || m.x >= (int)data->map->x)
				return (1);
			if (data->map->map[m.y * data->map->x + m.x] == 1)
				return (1);
			offset.x++;
		}
		offset.y++;
	}
	return (0);
}

void	cub_step(int dir, t_data *data)
{
	t_pos	new_pos;

	new_pos.x = data->player->pos.x + data->player->delta.x * (float)dir;
	new_pos.y = data->player->pos.y + data->player->delta.y * (float)dir;
	if (!cub_collision(data, data->player->pos.x, new_pos.y))
		data->player->pos.y = new_pos.y;
	else
		while (cub_collision(data, data->player->pos.x, data->player->pos.y))
			data->player->pos.y -= data->player->delta.y * 0.1F * dir;
	if (!cub_collision(data, new_pos.x, data->player->pos.y))
		data->player->pos.x = new_pos.x;
	else
		while (cub_collision(data, data->player->pos.x, data->player->pos.y))
			data->player->pos.x -= data->player->delta.x * 0.1F * dir;
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
		cub_turn(RIGHT, DEG_TO_RAD * 4, data->player);
	if (data->keys[KEY_LA])
		cub_turn(LEFT, DEG_TO_RAD * 4, data->player);
	if (data->keys[KEY_W])
		cub_step(FORWARD, data);
	if (data->keys[KEY_S])
		cub_step(BACKWARD, data);
	if (data->keys[KEY_D])
		cub_slide(RIGHT, data);
	if (data->keys[KEY_A])
		cub_slide(LEFT, data);
}
