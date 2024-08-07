/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:42:48 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/07 10:02:31 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// inline void	cub_draw_pixel(t_image *img, int x, int y, unsigned int color)
inline void	cub_draw_pixel(t_image *img, short x, short y, unsigned int color)
{
	char	*pixel;

	cub_tool_coord_norm(&x, &y);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	cub_draw_background(t_image *image)
{
	float			gradient;
	unsigned int	color;
	int				mid;
	int				x;
	int				y;

	mid = WIN_HEIGHT / 2 - 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		gradient = fabs(((float)y + (-WIN_HEIGHT * (y <= mid))) / mid) / 2;
		color = cub_adjust_brightness(image->back_colors[y >= mid], gradient);
		x = 0;
		while (x < WIN_WIDTH)
		{
			cub_draw_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	cub_draw(t_data *data)
{
	cub_draw_background(data->render);
	cub_draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->render->img, 0, 0);
}
