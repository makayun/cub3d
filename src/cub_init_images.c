/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:00:49 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/13 09:27:04 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_images(t_data *data)
{
	data->render->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->render->addr = mlx_get_data_addr(data->render->img, &data->render->bpp, &data->render->line_len, &data->render->endian);
	
}