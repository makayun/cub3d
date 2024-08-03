/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:09:15 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/03 00:00:46 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->render.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free (data->mlx);
	exit(EXIT_SUCCESS);
	return (42);
}

int	cub_key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cub_exit(data);
	else if (keysym == XK_d || keysym == XK_Right)
		data->player.pos.x += 4;
	else if (keysym == XK_a || keysym == XK_Left)
		data->player.pos.x -= 4;
	else if (keysym == XK_w || keysym == XK_Up)
		data->player.pos.y -= 4;
	else if (keysym == XK_s || keysym == XK_Down)
		data->player.pos.y += 4;
	cub_draw(data);
	return (ALL_FINE);
}

int	main()
{
	t_data	data;

	cub_init(&data);
	cub_draw(&data);
	mlx_key_hook(data.win, cub_key_handle, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &cub_exit, &data);
	mlx_loop(data.mlx);
}
