/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:00:49 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/23 16:29:28 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_images(t_data *data)
{
	int	i;
	char filename[4][FILENAME_MAX];
	
	data->render->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->render->addr = mlx_get_data_addr(data->render->img, &data->render->bpp, &data->render->line_len, &data->render->endian);
	ft_strlcpy(filename[WALL_EAST], "./assets/xpms/64/1.xpm", FILENAME_MAX);
	ft_strlcpy(filename[WALL_NORTH], "./assets/xpms/64/3.xpm", FILENAME_MAX);
	ft_strlcpy(filename[WALL_SOUTH], "./assets/xpms/64/6.xpm", FILENAME_MAX);
	ft_strlcpy(filename[WALL_WEST], "./assets/xpms/64/4.xpm", FILENAME_MAX);
	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, filename[i], &data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
		{
			printf (ANSI_RED "Wrong asset's path or filename: %s\n" ANSI_DEF, filename[i]);
			cub_exit(data);
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img, &data->texture[i].bpp, &data->texture[i].line_len, &data->texture[i].endian);
		i++;
	}

}