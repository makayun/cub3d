/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:00:21 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/28 15:09:10 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_print(t_data *data)
{
	printf ("\nAngle: %f, x: %f, y: %f, FOW: %d, res: %d\n",
		data->player->angle, data->player->pos.x, data->player->pos.y,
		data->player->fow, data->player->res);
	printf ("Coord: x: %d, y: %d\n",
		((int)data->player->pos.x / BLOCK),
		((int)data->player->pos.y / BLOCK));
}

void	cub_key_hold(int keysym, t_data *data)
{
	if (keysym == XK_Right)
		data->keys[KEY_RA] = 1;
	else if (keysym == XK_Left)
		data->keys[KEY_LA] = 1;
	else if (keysym == XK_w || keysym == XK_Up)
		data->keys[KEY_W] = 1;
	else if (keysym == XK_s || keysym == XK_Down)
		data->keys[KEY_S] = 1;
	else if (keysym == XK_d)
		data->keys[KEY_D] = 1;
	else if (keysym == XK_a)
		data->keys[KEY_A] = 1;
}

int	cub_key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cub_exit(data);
	else if (keysym == XK_equal)
		data->player->fow = ++data->player->fow - (data->player->fow > FOW_MAX);
	else if (keysym == XK_minus)
		data->player->fow = --data->player->fow + (data->player->fow < FOW_MIN);
	else if (keysym == XK_p)
		data->player->res *= 1 + (data->player->res < RES_MAX);
	else if (keysym == XK_o)
		data->player->res /= 1 + (data->player->res > RES_MIN);
	else if (keysym == XK_r)
		data->map->draw_rays = !data->map->draw_rays;
	else
		cub_key_hold(keysym, data);
	cub_print(data);
	return (ALL_FINE);
}

int	cub_key_release(int keysym, t_data *data)
{
	if (keysym == XK_Right)
		data->keys[KEY_RA] = 0;
	else if (keysym == XK_Left)
		data->keys[KEY_LA] = 0;
	else if (keysym == XK_w || keysym == XK_Up)
		data->keys[KEY_W] = 0;
	else if (keysym == XK_s || keysym == XK_Down)
		data->keys[KEY_S] = 0;
	else if (keysym == XK_d)
		data->keys[KEY_D] = 0;
	else if (keysym == XK_a)
		data->keys[KEY_A] = 0;
	cub_print(data);
	return (ALL_FINE);
}
