/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:05:49 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/25 22:32:25 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

inline void	cub_draw_pixel(t_image *img, int x, int y, unsigned int color)
{
	char	*pixel;

	cub_tool_coord_norm(&x, &y);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

inline void	cub_draw_square(t_image *image, t_coord coord, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			cub_draw_pixel(image, coord.x + j, coord.y + i, color);
			j++;
		}
		i++;
	}
}

void	cub_draw_line(t_image *image, t_coord start, t_coord end, int color)
{
	const t_coord	dlt = {abs(end.x - start.x), abs(end.y - start.y)};
	const t_coord	step = {1 - 2 * (start.x > end.x),
		1 - 2 * (start.y > end.y)};
	int				err;
	int				e2;

	err = (((dlt.x > dlt.y) * dlt.x) + ((dlt.y > dlt.x) * -dlt.y)) / 2;
	while (1)
	{
		cub_draw_pixel(image, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = err;
		err += (e2 > -dlt.x) * -dlt.y + (e2 < dlt.y) * dlt.x;
		start.x += (e2 > -dlt.x) * step.x;
		start.y += (e2 < dlt.y) * step.y;
	}
}
