/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/08 11:37:13 by maxmakagono      ###   ########.fr       */
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

void	cub_walls_draw(t_data *data, t_ray *ray, float dist)
{
	t_coord			pixel;
	t_coord			res;
	t_coord			offset;
	int				color;
	float			factor;
	
	res.y = WIN_HEIGHT * 24 / (dist + sqrt(dist)) ;
	res.x = (short)(WIN_WIDTH / data->player->res);
	offset.x = res.x * ray->num;
	offset.y = (WIN_HEIGHT - res.y) / 2;
	color = cub_wall_color(ray);
	factor = 0.2 * (-0.008 * dist);
	color = cub_adjust_brightness(color,  factor);
	pixel.y = 0;
	while (pixel.y < res.y)
	{
		pixel.x = 0;
		while (pixel.x < res.x)
		{
			cub_draw_pixel(data->render, pixel.x + offset.x, pixel.y + offset.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
}