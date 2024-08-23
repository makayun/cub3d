/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/23 13:18:07 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_get_pixel(t_image *img, short x, short y)
{
	char	*pixel;
	int  color;

	color =  0;
	cub_tool_coord_norm(&x, &y);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	ft_memcpy(&color, pixel, (img->bpp / 8));
	return (color);
}

// static inline int	cub_wall_color(t_ray *ray)
// {
// 	if (ray->hit == VERT)
// 	{
// 		if (ray->angle > SOUTH && ray->angle < NORTH)
// 			return (CYAN);
// 		return (MAGENTA);
// 	}
// 	else
// 	{
// 		if (ray->angle > WEST)
// 			return (YELLOW);
// 		return (GRAY);
// 	}
// }

int	cub_wall_side(t_ray *ray)
{
	if (ray->hit == VERT)
	{
		if (ray->angle > SOUTH && ray->angle < NORTH)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	else
	{
		if (ray->angle > WEST)
			return (WALL_NORTH);
		return (WALL_SOUTH);
	}
	// else
	// 	return (CUB_ERROR);
}

int	cub_walls_draw_texture(t_data *data, t_ray *ray, float *pos, float dist)
{
	// const t_coord	res = {WIN_WIDTH / data->player->res, WALL_Y_Q / dist};
	// const t_coord	off = {res.x * ray->num, (WIN_HEIGHT - res.y) >> 1};
	// t_coord			pix;
	const int	wall_side = cub_wall_side(ray);
	int			column;
	int			color;

	if (wall_side == WALL_WEST)
		column = ((int)((WIN_HEIGHT - pos[ray->hit]) * 4)) % 64;
	else if (wall_side == WALL_SOUTH)
		column = ((int)((WIN_WIDTH - pos[ray->hit]) * 4)) % 64;
	else
		column = ((int)(pos[ray->hit] * 4)) % 64;
	color = cub_get_pixel(&data->texture[wall_side], column, 0);
	(void)column;
	(void)data;
	(void)ray;
	(void)dist;
	return (color);
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
	const t_coord	res = {WIN_WIDTH / data->player->res, WALL_Y_Q / dist};
	const t_coord	off = {res.x * ray->num, (WIN_HEIGHT - res.y) >> 1};
	t_coord			pix;
	// const float		factor = 0.2F * (-0.004F * dist);
	// const int		color = cub_adjust_brightness(cub_wall_color(ray), factor);
	const int			color = cub_walls_draw_texture(data, ray,(float *)&ray->pos, dist);

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
