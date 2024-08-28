/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:38:09 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/28 14:22:24 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

inline int	cub_get_pixel(t_image *img, int x, int y)
{
	char	*pixel;
	int		color;

	cub_tool_coord_norm(&x, &y);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	ft_memcpy(&color, pixel, (img->bpp / 8));
	return (color);
}

inline int	cub_w_side(t_ray *ray)
{
	if (ray->hit == VERT)
	{
		if (ray->angle > SOUTH && ray->angle < NORTH)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	else if (ray->hit == HOR)
	{
		if (ray->angle > WEST)
			return (WALL_NORTH);
		return (WALL_SOUTH);
	}
	else
		return (CUB_ERROR);
}

inline int	cub_get_column(int w_side, float ray_hit_pos, int img_side)
{
	int	column;

	if (w_side == WALL_WEST)
		column = ((int)((WIN_HEIGHT - ray_hit_pos) * img_side / BLOCK))
			% img_side;
	else if (w_side == WALL_SOUTH)
		column = ((int)((WIN_WIDTH - ray_hit_pos) * img_side / BLOCK))
			% img_side;
	else
		column = ((int)(ray_hit_pos * img_side / BLOCK)) % img_side;
	return (column);
}

void	cub_wall_slice(t_data *data, t_ray *ray, float *pos, float dist)
{
	const t_coord	res = {WIN_WIDTH / data->player->res, WALL_Y_Q / dist};
	const t_coord	off = {res.x * ray->num, (WIN_HEIGHT - res.y) >> 1};
	const t_slice	s = {cub_w_side(ray), cub_get_column(s.w_side,
			pos[ray->hit], data->texture[s.w_side].height),
		(float)data->texture[s.w_side].height / (float)res.y,
		fabs((2560 - dist * 4) / (2560 + dist * 4))};
	t_coord			pix;
	int				color;

	pix.y = -1;
	while (++pix.y < res.y)
	{
		color = cub_adjust_brightness(cub_get_pixel(&data->texture[s.w_side],
					s.clmn, (int)(pix.y * s.y_q)), s.factor);
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
