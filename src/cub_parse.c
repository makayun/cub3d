/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:14:33 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/26 00:36:31 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	// else if (line[0] == 'F' && line[1] == ' ')
	// 	return (data->map->back_colors[FLOOR] = cub_parse_color(line), 1);
	// else if (line[0] == 'C' && line[1] == ' ')
	// 	return (data->map->back_colors[CEILING] = cub_parse_color(line), 1);
	if (wall > -1)
		return (ft_strlcpy(data->txtr_flnm[wall],
				ft_strchr(line, '.'), FILENAME_MAX), 1);
	return (0);
}

int	cub_parse(char *filename, t_data *data)
{
	char	*line;
	int		parameters;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == CUB_ERROR)
		return (printf(ANSI_RED"Error:\nCan't open the map!"ANSI_DEF),
			CUB_ERROR);
	line = "";
	parameters = 0;
	while (line && parameters < 4)
	{
		line = get_next_line(fd);
		parameters += cub_parse_parameters(line, data);
		free (line);
	}
	close (fd);
	if (!line && parameters < 4)
		return (printf(ANSI_RED"Error:\nCheck paramaters in the map!"ANSI_DEF),
			CUB_ERROR);
	return (ALL_FINE);
}
