/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:50:06 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/12 07:16:19 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

inline unsigned int	cub_adjust_brightness(int color, float factor)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned int	new_color;

	red = (unsigned char)(((color >> 16) & 0xFF) * factor);
	green = (unsigned char)(((color >> 8) & 0xFF) * factor);
	blue = (unsigned char)((color & 0xFF) * factor);
	new_color = (color & 0xFF000000) | (red << 16) | (green << 8) | blue;
	return (new_color);
}

inline void	cub_tool_coord_norm(short *x, short *y)
{
	*x *= (*x > 0);
	*y *= (*y > 0);
	*x += (*x > WIN_WIDTH) * (WIN_WIDTH - *x - 1);
	*y += (*y > WIN_HEIGHT) * (WIN_HEIGHT - *y - 1);
}

inline t_coord	cub_pos_to_coord(t_pos pos)
{
	t_coord	ret;

	ret.x = (int)(pos.x + 0.5);
	ret.y = (int)(pos.y + 0.5);
	return (ret);
}

inline float	cub_dist(t_pos a, t_pos b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
