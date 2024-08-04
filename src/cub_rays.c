/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/05 00:01:52 by maxmakagono      ###   ########.fr       */
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

void cub_rays(t_player *player, t_map *map, t_image *image)
{
	t_coord			m;
	t_position		ray;
	t_position		offset;
	int				ray_num;
	int				dof;
	unsigned int	mp;
	float			ray_angle;
	float			a_tan;

	ray_angle = player->angle;
	ray_num = 0;
	while (ray_num < 1)
	{
		dof = 0;
		a_tan = -1/tan(ray_angle);
		if (ray_angle > M_PI)
		{
			ray.y = (((int)player->pos.y >> 6) << 6) - 0.0001;
			ray.x = (player->pos.y - ray.y) * a_tan + player->pos.x;
			offset.y = -MAP_BLOCK;
			offset.x = -offset.y * a_tan;
		}
		else if (ray_angle < M_PI)
		{
			ray.y = (((int)player->pos.y >> 6) << 6) + MAP_BLOCK;
			ray.x = (player->pos.y - ray.y) * a_tan + player->pos.x;
			offset.y = MAP_BLOCK;
			offset.x = -offset.y * a_tan;
		}
		else if (ray_angle == 0 || ray_angle == (float)M_PI)
		{
			ray.x = player->pos.x;
			ray.y = player->pos.y;
			dof = 8;
		}
		// while (dof < 8)
		// {
		// 	m.x = (int)(ray.x) >> 6;
		// 	m.y = (int)(ray.y) >> 6;
		// 	mp = m.y * map->x + m.x;
		// 	if (mp < map->x * map->y && map->map[mp] == 1)
		// 		dof = 8;
		// 	else
		// 	{
		// 		ray.x += offset.x;
		// 		ray.y += offset.y;
		// 		dof++;
		// 	}
		// }
	while (dof < 8)
	{
		m.x = (int)(ray.x) >> 6;
		m.y = (int)(ray.y) >> 6;
		mp = m.y * map->x + m.x;

		// Check if ray is out of map bounds
		if (m.x < 0 || m.x >= (int)map->x || m.y < 0 || m.y >= (int)map->y)
		{
			printf("Ray out of bounds: x=%d, y=%d\n", m.x, m.y);
			break;
		}

		if (mp < map->x * map->y && map->map[mp] == 1)
		{
			printf("Wall hit at map[%d]: x=%d, y=%d\n", mp, m.x, m.y);
			dof = 8; // Exit loop when a wall is hit
		}
		else
		{
			ray.x += offset.x;
			ray.y += offset.y;
			dof++;
		}
	}
		ray_num++;
	}
	cub_draw_line(image, cub_pos_to_coord(player->pos), cub_pos_to_coord(ray), GREEN);
}