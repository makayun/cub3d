/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:50:06 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/07 12:59:55 by maxmakagono      ###   ########.fr       */
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
