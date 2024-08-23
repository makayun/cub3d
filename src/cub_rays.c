/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:18:41 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/23 10:38:08 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	cub_r_loop(t_pos offset, t_pos *r, t_map *map, t_player *player)
{
	t_coord			m;
	unsigned int	mp;

	while (1)
	{
		m.x = (int)(r->x) >> map->shift;
		m.y = (int)(r->y) >> map->shift;
		mp = m.y * map->x + m.x;
		if (m.x < 0 || m.x >= (int)map->x || m.y < 0 || m.y >= (int)map->y)
			return ((float)INT_MAX);
		else if (mp < map->size && map->map[mp] == 1)
			return (cub_dist(player->pos, *r));
		else
		{
			r->x += offset.x;
			r->y += offset.y;
		}
	}
}

float	cub_ray_hit_hor(t_player *player, t_map *map, t_pos *r, float r_angle)
{
	t_pos		offset;
	const float	a_tan = -1 / tan(r_angle);

	if (r_angle > M_PI)
	{
		r->y = (((int)player->pos.y >> map->shift) << map->shift) - 0.0001F;
		offset.y = -BLOCK;
	}
	else if (r_angle < M_PI)
	{
		r->y = (((int)player->pos.y >> map->shift) << map->shift) + BLOCK;
		offset.y = BLOCK;
	}
	else
		return ((float)INT_MAX);
	r->x = (player->pos.y - r->y) * a_tan + player->pos.x;
	offset.x = -offset.y * a_tan;
	return (cub_r_loop(offset, r, map, player));
}

float	cub_ray_hit_vert(t_player *player, t_map *map, t_pos *r, float r_angle)
{
	t_pos		offset;
	const float	neg_tan = -tan(r_angle);

	if (r_angle > M_PI_2 && r_angle < (3 * M_PI_2))
	{
		r->x = (((int)player->pos.x >> map->shift) << map->shift) - 0.0001F;
		offset.x = -BLOCK;
	}
	else if (r_angle < M_PI_2 || r_angle > (3 * M_PI_2))
	{
		r->x = (((int)player->pos.x >> map->shift) << map->shift) + BLOCK;
		offset.x = BLOCK;
	}
	else
		return ((float)INT_MAX);
	r->y = (player->pos.x - r->x) * neg_tan + player->pos.y;
	offset.y = -offset.x * neg_tan;
	return (cub_r_loop(offset, r, map, player));
}

void	cub_rays_n_walls(t_player *player, t_map *map, t_data *data)
{
	t_ray		r;
	float		fish_dist;
	const float	angle_step = DEG_TO_RAD * player->fow / player->res;

	r.angle = player->angle - DEG_TO_RAD * player->fow / 2;
	r.num = 0;
	while (r.num < player->res)
	{
		r.angle += (r.angle < 0) * PI_TWICE - (r.angle > PI_TWICE) * PI_TWICE;
		r.dist[HOR] = cub_ray_hit_hor(player, map, &r.hit_pos[HOR], r.angle);
		r.dist[VERT] = cub_ray_hit_vert(player, map, &r.hit_pos[VERT], r.angle);
		r.hit = r.dist[VERT] < r.dist[HOR];
		fish_dist = cub_fisheye(data, r.angle, r.dist[r.hit]);
		cub_walls_draw(data, &r, fish_dist);
		r.pos = r.hit_pos[r.hit];
		if (map->draw_rays)
			cub_draw_line(data->render, cub_pos_to_coord(player->pos),
				cub_pos_to_coord(r.pos), GREEN);
		r.angle += angle_step;
		r.num++;
	}
	// printf("x: %f	y: %f\n", r.pos.x, r.pos.y);
	cub_walls_draw_texture(data, &r, (float *)&r.pos, fish_dist);
}
