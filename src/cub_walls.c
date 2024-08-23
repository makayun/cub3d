/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/23 16:28:35 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_get_pixel(t_image *img, int x, int y)
{
	char	*pixel;
	int  color;

	// color =  0;
	cub_tool_coord_norm(&x, &y);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	ft_memcpy(&color, pixel, (img->bpp / 8));
	return (color);
}

int	cub_wall_side(t_ray *ray)
{
	if (ray->hit == VERT)
	{
		if (ray->angle > SOUTH && ray->angle < NORTH)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	else  if (ray->hit == HOR)
	{
		if (ray->angle > WEST)
			return (WALL_NORTH);
		return (WALL_SOUTH);
	}
	else
		return (CUB_ERROR);
}

int		cub_get_column(int wall_side,  float ray_hit_pos)
{
	int	column;
	
	if (wall_side == WALL_WEST)
		column = ((int)((WIN_HEIGHT - ray_hit_pos) * 4)) % 64;
	else if (wall_side == WALL_SOUTH)
		column = ((int)((WIN_WIDTH - ray_hit_pos) * 4)) % 64;
	else
		column = ((int)(ray_hit_pos * 4)) % 64;
	return (column);
}

void	cub_slice(t_data *data, t_ray *ray, float *pos, float dist)
{
	const t_coord	res = {WIN_WIDTH / data->player->res, WALL_Y_Q / dist};
	const t_coord	off = {res.x * ray->num, (WIN_HEIGHT - res.y) >> 1};
	t_coord			pix;
	const int		wall_side = cub_wall_side(ray);	
	const int		column = cub_get_column(wall_side, pos[ray->hit]);
	int				color;
	const float		y_q = (float)data->texture[wall_side].height / (float)res.y;

	pix.y = -1;
	while (++pix.y < res.y)
	{
		color = cub_get_pixel(&data->texture[wall_side], column, (int)(pix.y * y_q));
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
