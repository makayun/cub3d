/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:23:40 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/08 11:25:25 by maxmakagono      ###   ########.fr       */
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

void	cub_step(int dir, t_player *player)
{
	player->pos.x += player->delta.x * (float)dir;
	player->pos.y += player->delta.y * (float)dir;
}

void	cub_slide(int dir, t_player *player)
{
	cub_turn(dir, M_PI_2, player);
	cub_step(FORWARD, player);
	cub_turn(-dir, M_PI_2, player);
}