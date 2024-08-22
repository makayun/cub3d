/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/22 13:47:32 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static inline int	cub_wall_color(t_ray *ray)
{
	if (ray->hit == VERT)
	{
		if (ray->angle > SOUTH && ray->angle < NORTH)
			return (CYAN);
		return (MAGENTA);
	}
	else
	{
		if (ray->angle > WEST)
			return (YELLOW);
		return (GRAY);
	}
}

int	cub_wall_texture(t_ray *ray)
{
	if (ray->hit == VERT)
	{
		if (ray->angle > SOUTH && ray->angle < NORTH)
			return (TXTR_WEST);
		return (TXTR_EAST);
	}
	else
	{
		if (ray->angle > WEST)
			return (TXTR_NORTH);
		return (TXTR_SOUTH);
	}
}

void	cub_walls_draw_texture(t_data *data, t_ray *ray, float dist)
{
	
	// int	column;

	// column = 
	(void)data;
	(void)ray;
	(void)dist;
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
	const float		factor = 0.2F * (-0.004F * dist);

	res.y = WALL_Y_Q / dist;
	res.x = (short)(WIN_WIDTH / data->player->res);
	off.x = res.x * ray->num;
	off.y = (WIN_HEIGHT - res.y) >> 1;
	color = cub_adjust_brightness(cub_wall_color(ray), factor);
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
