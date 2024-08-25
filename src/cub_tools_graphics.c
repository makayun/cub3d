/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:10:17 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/25 22:11:34 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

inline int	cub_adjust_brightness(int color, float factor)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				new_color;

	red = (unsigned char)(((color >> 16) & 0xFF) * factor);
	green = (unsigned char)(((color >> 8) & 0xFF) * factor);
	blue = (unsigned char)((color & 0xFF) * factor);
	new_color = (color & 0x00000000) | (red << 16) | (green << 8) | blue;
	return (new_color);
}

inline float	cub_tool_fisheye(t_data *data, float ray_angle, float ray_dist)
{
	float	fish_angle;

	fish_angle = data->player->angle - ray_angle;
	fish_angle += (fish_angle < 0) * PI_TWICE;
	fish_angle -= (fish_angle > PI_TWICE) * PI_TWICE;
	return (ray_dist * cos(fish_angle) + sqrt(ray_dist));
}
