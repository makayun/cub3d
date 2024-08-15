/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:58:59 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/14 15:47:37 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_player(t_data *data)
{
	data->player->pos.x = BLOCK + BLOCK / 2;
	data->player->pos.y = BLOCK + BLOCK / 2;
	data->player->angle = M_PI_2;
	data->player->delta.x = cos(data->player->angle) * STEP;
	data->player->delta.y = sin(data->player->angle) * STEP;
	data->player->fow = FOW_MAX / 2;
	data->player->res = WIN_WIDTH;
}
