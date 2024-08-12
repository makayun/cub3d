/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/12 08:49:05 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static inline int	cub_wall_color(t_ray *ray)
{
	if (ray->vert_hit)
	{
		if (ray->angle > M_PI_2 && ray->angle < (3 * M_PI_2))
			return (CYAN);
		return (MAGENTA);
	}
	else
	{
		if (ray->angle > M_PI)
			return (YELLOW);
		return (GRAY);
	}
}

inline float	cub_fisheye(t_data *data, float ray_angle, float ray_dist)
{
	float	fish_angle;

	fish_angle = data->player->angle - ray_angle;
	fish_angle += (fish_angle < 0) * PI_TWICE;
	fish_angle -= (fish_angle > PI_TWICE) * PI_TWICE;
	return (ray_dist * cos(fish_angle) + sqrt(ray_dist));
}

void	cub_walls_draw(t_data *data, t_ray *ray, float dist)
{
	t_coord			pix;
	t_coord			res;
	t_coord			off;
	int				color;
	float			factor;

	res.y = WALL_Y_Q / dist;
	res.x = (short)(WIN_WIDTH / data->player->res);
	off.x = res.x * ray->num;
	off.y = (WIN_HEIGHT - res.y) >> 1;
	color = cub_wall_color(ray);
	factor = 0.2F * (-0.008F * dist);
	color = cub_adjust_brightness(color, factor);
	pix.y = -1;
	while (++pix.y < res.y)
	{
		pix.x = -1;
		while (++pix.x < res.x)
		{
			if (!(pix.y + off.y < data->map->h
					&& pix.x + off.x + 1 <= data->map->w))
				cub_draw_pixel(data->render,
					pix.x + off.x, pix.y + off.y, color);
		}
	}
}
