/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays_n_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/07 23:16:56 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	cub_ray_loop(t_position offset, t_position *ray, t_map *map, t_player *player)
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
		else if (mp < map->size && map->map[mp] == 1)
			return (cub_dist(player->pos, *ray));
		else
		{
			ray->x += offset.x;
			ray->y += offset.y;
		}
	}
}

float	cub_ray_check_horizontal(t_player *player, t_map *map, t_position *ray, float ray_angle)
{
	t_position	offset;
	float		a_tan;

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

float	cub_ray_check_vertical(t_player *player, t_map *map, t_position *ray, float ray_angle)
{
	t_position	offset;
	float		neg_tan;

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

void	cub_rays_n_walls(t_player *player, t_map *map, t_data *data)
{
	t_ray	ray;
	float	angle_step;
	float	fish_dist;

	angle_step = DEG_TO_RAD * player->fow / player->res;
	ray.angle = player->angle - DEG_TO_RAD * player->fow / 2;
	ray.num = 0;
	// while (ray.num < player->fow)
	while (ray.num < player->res)
	{
		ray.angle += (ray.angle < 0) * PI_TWICE - (ray.angle > PI_TWICE) * PI_TWICE;
		ray.dist[HOR] = cub_ray_check_horizontal(player, map, &ray.hit[HOR], ray.angle);
		ray.dist[VERT] = cub_ray_check_vertical(player, map, &ray.hit[VERT], ray.angle);
		ray.vert_hit = ray.dist[VERT] < ray.dist[HOR];
		fish_dist = cub_fix_fisheye(data, ray.angle, ray.dist[ray.dist[VERT] < ray.dist[HOR]]);
		// ray.pos = ray.hit[ray.vert_hit];
		cub_walls_draw(data, &ray, fish_dist);
		// ray.angle += DEG_TO_RAD;
		ray.angle += angle_step;
		ray.num++;
	}
}
