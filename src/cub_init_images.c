/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:00:49 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/26 00:06:02 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_images(t_data *data, t_image *render, t_image *texture)
{
	int	i;

	render->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	render->addr = mlx_get_data_addr(render->img, &render->bpp,
			&render->line_len, &render->endian);
	i = 0;
	while (i < 4)
	{
		texture[i].img = mlx_xpm_file_to_image(data->mlx, data->txtr_flnm[i],
				&texture[i].width, &texture[i].height);
		if (!texture[i].img)
		{
			printf (ANSI_RED "Wrong asset's path or filename: %s\n" ANSI_DEF,
				data->txtr_flnm[i]);
			cub_exit(data);
		}
		texture[i].addr = mlx_get_data_addr(texture[i].img, &texture[i].bpp,
				&texture[i].line_len, &texture[i].endian);
		i++;
	}
}
