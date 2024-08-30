/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:41:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/30 15:40:16 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit (EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "let's fly!");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free (data->mlx);
		exit (EXIT_FAILURE);
	}
}

int	cub_init_player(t_data *data, int x, int y, char dir)
{
	if (dir == 'W')
		data->player->angle = WEST;
	else if (dir == 'E')
		data->player->angle = EAST;
	else if (dir == 'N')
		data->player->angle = NORTH;
	else if (dir == 'S')
		data->player->angle = SOUTH;
	else
		return (NOT_YET);
	data->player->pos.x = x * BLOCK + BLOCK / 2;
	data->player->pos.y = y * BLOCK + BLOCK / 2;
	data->player->delta.x = cos(data->player->angle) * STEP;
	data->player->delta.y = sin(data->player->angle) * STEP;
	data->player->fow = FOW_MAX / 2;
	data->player->res = RES_MAX;
	return (ALL_FINE);
}

int	cub_init_map(t_data *data, bool *map, char tmp[MAP_H_MAX][MAP_W_MAX])
{
	unsigned int		x;
	unsigned int		y;
	size_t				line_len;
	int					player_inited;

	player_inited = 0;
	y = 0;
	while (y < data->map->y)
	{
		line_len = ft_strlen(tmp[y]);
		x = 0;
		while (x < line_len)
		{
			player_inited += cub_init_player(data, x, y, tmp[y][x]);
			*(map++) = (tmp[y][x++] == '1');
		}
		while (x++ < data->map->x)
			*(map++) = 0;
		y++;
	}
	if (player_inited != 1)
		return (printf(T_RED"Error:\nCheck the player!\n"T_DEF), CUB_ERROR);
	return (ALL_FINE);
}

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
			printf (T_RED "Wrong asset's path or filename: %s\n" T_DEF,
				data->txtr_flnm[i]);
			cub_exit(data);
		}
		texture[i].addr = mlx_get_data_addr(texture[i].img, &texture[i].bpp,
				&texture[i].line_len, &texture[i].endian);
		i++;
	}
}

void	cub_init(char **argv, t_data *data)
{
	int	i;

	data->exit_code = EXIT_FAILURE;
	if (cub_parse(argv[1], data) == CUB_ERROR)
		exit (EXIT_FAILURE);
	if (data->map->x >= MAP_W_MAX || data->map->y >= MAP_H_MAX)
	{
		printf(T_RED"Error:\nThe map is too big!\n"T_DEF);
		exit(EXIT_FAILURE);
	}
	data->map->size = data->map->x * data->map->y;
	data->map->shift = log2(BLOCK);
	data->map->h = data->map->y * BLOCK;
	data->map->w = data->map->x * BLOCK;
	data->map->draw_rays = 0;
	cub_init_mlx(data);
	cub_init_images(data, data->render, data->texture);
	i = 0;
	while (i < 6)
		data->keys[i++] = 0;
	data->exit_code = EXIT_SUCCESS;
}
