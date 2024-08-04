// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cub_rays.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/04 13:12:36 by maxmakagono       #+#    #+#             */
// /*   Updated: 2024/08/04 22:18:29 by maxmakagono      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../cub3d.h"

// void cub_rays(t_data *data, t_player *player)
// {
// 	int		ray, mx, my, mp, dof;
// 	float	ray_x, ray_y, ray_angle, x_offset, y_offset;
// 	float	a_tan;

// 	ray_angle = player->angle;
// 	ray = 0;
// 	while (ray < 1)
// 	{
// 		dof = 0;
// 		a_tan = -1/tan(ray_angle);
// 		if (ray_angle > M_PI)
// 		{
// 			ray_y = (((int)player->pos.y >> 6) << 6) - 0.0001;
// 			ray_x = (player->pos.y - ray_y) * a_tan + player->pos.x;
// 			y_offset = -MAP_BLOCK;
// 			x_offset = -y_offset * a_tan;
// 		}
// 		else if (ray_angle < M_PI)
// 		{
// 			ray_y = (((int)player->pos.y >> 6) << 6) + MAP_BLOCK;
// 			ray_x = (player->pos.y - ray_y) * a_tan + player->pos.x;
// 			y_offset = -MAP_BLOCK;
// 			x_offset = -y_offset * a_tan;
// 		}
// 		else if (ray_angle == 0 || ray_angle == (float)M_PI)
// 		{
// 			ray_x = player->pos.x;
// 			ray_y = player->pos.y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(ray_x) / MAP_BLOCK;
// 			my = 
// 		}
// 		ray++;
// 	}
	

// }