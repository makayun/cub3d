/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/06 02:19:59 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_coord	cub_pos_to_coord(t_position pos)
{
	t_coord ret;

	ret.x = (int)(pos.x + 0.5);
	ret.y = (int)(pos.y + 0.5);
	return (ret);
}

float	cub_dist(t_position a, t_position b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void cub_rays(t_player *player, t_map *map, t_image *image)
{
	t_coord			m;
	t_position		ray;
	t_position		hor_pos;
	t_position		vert_pos;
	t_position		offset;
	float			h_hit_dist;
	float			v_hit_dist;
	int				ray_num;
	unsigned int	mp;
	float			ray_angle;
	float			a_tan;
	float			neg_tan;

	ray_angle = player->angle;
	ray_num = 0;
	while (ray_num < 1)
	{
		// Check horizontal lines
		a_tan = -1/tan(ray_angle);
		h_hit_dist = INT32_MAX;
		if (ray_angle > M_PI) // looking up
		{
			ray.y = (((int)player->pos.y >> 4) << 4) - 0.0001;
			ray.x = (player->pos.y - ray.y) * a_tan + player->pos.x;
			offset.y = -MAP_BLOCK;
			offset.x = -offset.y * a_tan;

		}
		else if (ray_angle < M_PI) // looking down
		{
			ray.y = (((int)player->pos.y >> 4) << 4) + MAP_BLOCK;
			ray.x = (player->pos.y - ray.y) * a_tan + player->pos.x;
			offset.y = MAP_BLOCK;
			offset.x = -offset.y * a_tan;
		}
		while (1)
		{
			m.x = (int)(ray.x) >> 4;
			m.y = (int)(ray.y) >> 4;
			mp = m.y * map->x + m.x;
			if (m.x < 0 || m.x >= (int)map->x || m.y < 0 || m.y >= (int)map->y)
				break ;
			else if (mp > 0 && mp < map->size && map->map[mp] == 1)
			{
				hor_pos = ray;
				h_hit_dist = cub_dist(player->pos, hor_pos);
				break ;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
			}
		}
		// Check vertical lines
		neg_tan = -tan(ray_angle);
		v_hit_dist = INT32_MAX;
		if (ray_angle > M_PI_2 && ray_angle < (3 * M_PI_2)) // looking left
		{
			ray.x = (((int)player->pos.x >> 4) << 4) - 0.0001;
			ray.y = (player->pos.x - ray.x) * neg_tan + player->pos.y;
			offset.x = -MAP_BLOCK;
			offset.y = -offset.x * neg_tan;
		}
		else if (ray_angle < M_PI_2 || ray_angle > (3 * M_PI_2)) // looking right
		{
			ray.x = (((int)player->pos.x >> 4) << 4) + MAP_BLOCK;
			ray.y = (player->pos.x - ray.x) * neg_tan + player->pos.y;
			offset.x = MAP_BLOCK;
			offset.y = -offset.x * neg_tan;
		}
		while (1)
		{
			m.x = (int)(ray.x) >> 4;
			m.y = (int)(ray.y) >> 4;
			mp = m.y * map->x + m.x;
			if (m.x < 0 || m.x >= (int)map->x || m.y < 0 || m.y >= (int)map->y)
				break ;
			else if (mp > 0 && mp < map->size && map->map[mp] == 1)
			{
				vert_pos = ray;
				v_hit_dist = cub_dist(player->pos, vert_pos);
				break ;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
			}
		}
		if (h_hit_dist < v_hit_dist)
			ray = hor_pos;
		else
			ray = vert_pos;
		cub_draw_line(image, cub_pos_to_coord(player->pos), cub_pos_to_coord(ray), GREEN);
		ray_num++;
	}
}
