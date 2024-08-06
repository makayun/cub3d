/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/06 16:52:07 by maxmakagono      ###   ########.fr       */
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

float cub_ray_loop(t_position offset, t_position *ray, t_map *map, t_player *player)
{
	t_coord			m;
	unsigned int	mp;

	while (1)
	{
		m.x = (int)(ray->x) >> map->shift;
		m.y = (int)(ray->y) >> map->shift;
		mp = m.y * map->x + m.x;
		if (m.x < 0 || m.x >= (int)map->x || m.y < 0 || m.y >= (int)map->y)
			return (INT_MAX);
		else if (mp > 0 && mp < map->size && map->map[mp] == 1)
			return (cub_dist(player->pos, *ray));
		else
		{
			ray->x += offset.x;
			ray->y += offset.y;
		}
	}
}

float cub_ray_check_horizontal(t_player *player, t_map *map, t_position *ray, float ray_angle)
{
	float		a_tan;
	t_position	offset;

	a_tan = -1/tan(ray_angle);
	if (ray_angle > M_PI)
	{
		ray->y = (((int)player->pos.y >> map->shift) << map->shift) - 0.0001;
		offset.y = -MAP_BLOCK;
	}
	else if (ray_angle < M_PI)
	{
		ray->y = (((int)player->pos.y >> map->shift) << map->shift) + MAP_BLOCK;
		offset.y = MAP_BLOCK;
	}
		ray->x = (player->pos.y - ray->y) * a_tan + player->pos.x;
		offset.x = -offset.y * a_tan;
	return (cub_ray_loop(offset, ray, map, player));
}

float cub_ray_check_vertical(t_player *player, t_map *map, t_position *ray, float ray_angle)
{
	float		neg_tan;
	t_position	offset;

	neg_tan = -tan(ray_angle);
	if (ray_angle > M_PI_2 && ray_angle < (3 * M_PI_2))
	{
		ray->x = (((int)player->pos.x >> map->shift) << map->shift) - 0.0001;
		offset.x = -MAP_BLOCK;
	}
	else if (ray_angle < M_PI_2 || ray_angle > (3 * M_PI_2))
	{
		ray->x = (((int)player->pos.x >> map->shift) << map->shift) + MAP_BLOCK;
		offset.x = MAP_BLOCK;
	}
		ray->y = (player->pos.x - ray->x) * neg_tan + player->pos.y;
		offset.y = -offset.x * neg_tan;
	return (cub_ray_loop(offset, ray, map, player));
}

void cub_rays(t_player *player, t_map *map, t_image *image)
{
	t_position		hit_check[2];
	t_position		ray;
	float			hit_dist[2];
	float			ray_angle;
	int				ray_num;

	ray_angle = player->angle - DEG_TO_RAD * player->fow / 2;
	ray_num = 0;
	while (ray_num < player->fow)
	{
		ray_angle += (ray_angle < 0) * PI_TWICE - (ray_angle > PI_TWICE) * PI_TWICE;
		hit_dist[HOR] = cub_ray_check_horizontal(player, map, &hit_check[HOR], ray_angle);
		hit_dist[VERT] = cub_ray_check_vertical(player, map, &hit_check[VERT], ray_angle);
		ray = hit_check[hit_dist[VERT] < hit_dist[HOR]];
		cub_draw_line(image, cub_pos_to_coord(player->pos), cub_pos_to_coord(ray), GREEN);
		ray_angle += DEG_TO_RAD;
		ray_num++;
	}
}
