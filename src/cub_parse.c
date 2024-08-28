/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:14:33 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/28 14:26:02 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	cub_parse_color(char *line)
{
	int		color[3];
	int		ret;
	int		i;

	if (!line || !*line)
		return (0);
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(line) % 256;
		line = ft_strchr(line, ',');
		if (line && *line == ',')
			line++;
		i++;
	}
	ret = color[0] << 16 | color[1] << 8 | color[2];
	return (ret);
}

int	cub_parse_parameters(char *line, t_data *data)
{
	int		wall;
	char	*nl;

	if (!line || !*line)
		return (0);
	nl = ft_strchr(line, '\n');
	if (nl && *nl)
		*nl = 0;
	wall = -1;
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		wall = WALL_WEST;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		wall = WALL_EAST;
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		wall = WALL_NORTH;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		wall = WALL_SOUTH;
	else if (line[0] == 'F' && line[1] == ' ')
		return (data->map->back_colors[FLOOR] = cub_parse_color(line + 1), 1);
	else if (line[0] == 'C' && line[1] == ' ')
		return (data->map->back_colors[CEILING] = cub_parse_color(line + 1), 1);
	if (wall > -1)
		return (ft_strlcpy(data->txtr_flnm[wall],
				cub_cut_whitespace(line + 3), FILENAME_MAX), 1);
	return (0);
}

int	cub_parse_map(t_data *data, t_map *map, int fd)
{
	char	*line;
	char	*nl;
	char	temp_map[MAP_H_MAX][MAP_W_MAX];

	line = "";
	map->x = 0;
	map->y = 0;
	while (line)
	{
		line = get_next_line(fd);
		nl = ft_strchr(line, '\n');
		if (nl && *nl)
			*nl = 0;
		if (!line || !*line)
			continue ;
		map->x += (map->x < ft_strlen(line)) * (ft_strlen(line) - map->x);
		ft_strcpy(temp_map[map->y], line);
		free (line);
		if (++map->y >= MAP_H_MAX)
			return (CUB_ERROR);
	}
	return (cub_init_map(data, map->map, temp_map));
}

int	cub_parse(char *filename, t_data *data)
{
	char	*line;
	int		parameters;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == CUB_ERROR)
		return (printf(T_RED"Error:\nCan't open the map!"T_DEF), CUB_ERROR);
	line = "";
	parameters = 0;
	while (line && parameters < 6)
	{
		line = get_next_line(fd);
		parameters += cub_parse_parameters(line, data);
		free (line);
	}
	if (parameters < 6)
	{
		close(fd);
		printf(T_RED"Error:\nCheck paramaters in the map!"T_DEF);
		return (CUB_ERROR);
	}
	if (cub_parse_map(data, data->map, fd) == CUB_ERROR)
		return (close(fd), CUB_ERROR);
	close (fd);
	return (ALL_FINE);
}
