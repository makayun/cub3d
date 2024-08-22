/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:00:49 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/22 13:36:38 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_images(t_data *data)
{
	int	i;
	
	data->render->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->render->addr = mlx_get_data_addr(data->render->img, &data->render->bpp, &data->render->line_len, &data->render->endian);
	ft_strlcpy(data->assets->filename[0], "./assets/xpms/64/1.xpm", FILENAME_MAX);
	ft_strlcpy(data->assets->filename[1], "./assets/xpms/64/2.xpm", FILENAME_MAX);
	ft_strlcpy(data->assets->filename[2], "./assets/xpms/64/3.xpm", FILENAME_MAX);
	ft_strlcpy(data->assets->filename[3], "./assets/xpms/64/4.xpm", FILENAME_MAX);
	i = 0;
	while (i < 4)
	{
		data->assets->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->assets->filename[i], &data->assets->texture[i].width, &data->assets->texture[i].height);
		if (!data->assets->texture[i].img)
		{
			printf (ANSI_RED "Wrong asset's path or filename: %s\n" ANSI_DEF, data->assets->filename[i]);
			cub_exit(data);
		}
		data->assets->texture[i].addr = mlx_get_data_addr(data->assets->texture[i].img, &data->assets->texture[i].bpp, &data->assets->texture[i].line_len, &data->assets->texture[i].endian);
		i++;
	}

}