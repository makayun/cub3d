/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/06 00:16:59 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_coord	cub_pos_to_coord(t_position pos)
{
	t_coord ret;

	ret.x = (int)pos.x ;
	ret.y = (int)pos.y;
	return (ret);
}

// float	dist(t_position a, t_position b, float angle)
// {
// 	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
// }

void cub_rays(t_player *player, t_map *map, t_image *image)
{
	t_coord			m;
	t_position		ray;
	t_position		offset;
	bool			h_hit;
	bool			v_hit;
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
			{
				printf(ANSI_RED "Horizontal lines: Ray out of bounds: x=%d, y=%d\n" ANSI_DEF, m.x, m.y);
				h_hit = 0;
				break ;
			}
			else if (mp > 0 && mp < map->size && map->map[mp] == 1)
			{
				printf(ANSI_RED "Horizontal lines: Wall hit at map[%d]: x=%d, y=%d\n" ANSI_DEF, mp, m.x, m.y);
				h_hit = 1;
				break ;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
			}
		}
		if (h_hit)
			cub_draw_line(image, cub_pos_to_coord(player->pos), cub_pos_to_coord(ray), RED);
		// Check vertical lines
		neg_tan = -tan(ray_angle);
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
			{
				printf(ANSI_GREEN "Vertical lines: Ray out of bounds: x=%d, y=%d\n" ANSI_DEF, m.x, m.y);
				v_hit = 0;
				break ;
			}
			else if (mp > 0 && mp < map->size && map->map[mp] == 1)
			{
				printf(ANSI_GREEN "Vertical lines: Wall hit at map[%d]: x=%d, y=%d\n" ANSI_DEF, mp, m.x, m.y);
				v_hit = 1;
				break ;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
			}
		}
		if (v_hit)
			cub_draw_line(image, cub_pos_to_coord(player->pos), cub_pos_to_coord(ray), GREEN);
		ray_num++;
	}
}
