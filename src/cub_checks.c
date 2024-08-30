/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:19:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/30 15:51:32 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_check_input(int argc, char *filename)
{
	if (argc <= 1)
	{
		perror(T_RED"Error:\nPlease, choose a map and try again\n"T_DEF);
		return (CUB_ERROR);
	}
	else if (argc > 2)
	{
		perror(T_RED"Error:\nToo many arguments, try again!\n"T_DEF);
		return (CUB_ERROR);
	}
	else if (!ft_strnstr(filename, ".cub", ft_strlen(filename))
		|| !ft_strnstr(filename, "./", 2))
	{
		perror(T_RED"Error:\nWrong map filename!\n"T_DEF);
		return (CUB_ERROR);
	}
	else
		return (ALL_FINE);
}

int	cub_check_map_p(char map[MAP_H_MAX][MAP_W_MAX], t_data *data, int x, int y)
{
	int	left;
	int	right;
	int	up;
	int	down;

	if (x < 0 || x >= (int)data->map->x || y < 0 || y >= (int)data->map->y)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	left = cub_check_map_p(map, data, x - 1, y);
	right = cub_check_map_p(map, data, x + 1, y);
	up = cub_check_map_p(map, data, x, y - 1);
	down = cub_check_map_p(map, data, x, y + 1);
	return (left && right && up && down);
}

int	cub_check_map(char map[MAP_H_MAX][MAP_W_MAX], t_data *data)
{
	const int	x = ((int)data->player->pos.x / BLOCK);
	const int	y = ((int)data->player->pos.y / BLOCK);

	if (cub_check_map_p(map, data, x, y) == 0)
	{
		printf(T_RED"Error:\nThe player is not surrounded by walls!\n"T_DEF);
		return (CUB_ERROR);
	}
	return (ALL_FINE);
}
