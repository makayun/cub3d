/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/10 08:39:06 by maxmakagono      ###   ########.fr       */
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

inline float	cub_fix_fisheye(t_data *data, float ray_angle, float ray_dist)
{
	float	fish_angle;

	fish_angle = data->player->angle - ray_angle;
	fish_angle += (fish_angle < 0) * PI_TWICE;
	fish_angle -= (fish_angle > PI_TWICE) * PI_TWICE;
    return (ray_dist * cos(fish_angle) + sqrt(ray_dist));
}

void	cub_walls_draw(t_data *data, t_ray *ray, float dist)
{
	t_coord			pixel;
	t_coord			res;
	t_coord			offset;
	int				color;
	float			factor;
    
    res.y = WALL_Y_Q / dist;
	res.x = (short)(WIN_WIDTH / data->player->res);
	offset.x = res.x * ray->num;
    offset.y = (WIN_HEIGHT - res.y) >> 1;
	color = cub_wall_color(ray);
	factor = 0.2F * (-0.008F * dist);
	color = cub_adjust_brightness(color,  factor);
	pixel.y = 0;
	while (pixel.y < res.y)
	{
		pixel.x = 0;
		while (pixel.x < res.x)
		{
			if (!(pixel.y + offset.y < data->map->height && pixel.x + offset.x + 1 <= data->map->width))
				cub_draw_pixel(data->render, pixel.x + offset.x, pixel.y + offset.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
}
