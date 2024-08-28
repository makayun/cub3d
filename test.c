#include <stdio.h>
#include <math.h>
#include "cub3d.h"

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
		return (1);
	else if (line[0] == 'C' && line[1] == ' ')
		return (1);
	if (wall > -1)
		return (1);
	return (0);
}

void	cub_init_player_new(t_data *data, int x, int y, char dir)
{
	data->player->pos.x = x * BLOCK + BLOCK / 2;
	data->player->pos.y = y * BLOCK + BLOCK / 2;
	if (dir == 'W')
		data->player->angle = WEST;
	else if (dir == 'E')
		data->player->angle = EAST;
	else if (dir == 'N')
		data->player->angle = NORTH;
	else if (dir == 'S')
		data->player->angle = SOUTH;
	data->player->delta.x = cos(data->player->angle) * STEP;
	data->player->delta.y = sin(data->player->angle) * STEP;
	data->player->fow = FOW_MAX / 2;
	data->player->res = RES_MAX;
}

int	cub_parse_map(t_data *data, bool *map, int fd)
{
	char	*line;
	char	*nl;
	size_t	line_len;
	int		i;

	line = "";
	data->map->x = 0;
	data->map->y = 0;
	while (line)
	{
		line = get_next_line(fd);
		nl = ft_strchr(line, '\n');
		if (nl && *nl)
			*nl = 0;
		if (!line || !*line)
			continue ;
		line_len = ft_strlen(line);
		if (MAP_WIDTH_MAX <= line_len)
			return (free(line), CUB_ERROR);
		data->map->x = (data->map->x < line_len) * line_len;
		i = 0;
		while (i < line_len)
		{
			if (line[i] == 'W' || line[i] == 'E' || line[i] == 'N' || line[i] == 'S')
				cub_init_player_new(data, i, data->map->y, line[i]);
			*(map++) = (line[i++] == '1');
		}
		free (line);
		if (MAP_HEIGHT_MAX <= ++data->map->y)
			return(CUB_ERROR);
	}
	return (ALL_FINE);
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
	while (line && parameters < 6)
	{
		line = get_next_line(fd);
		parameters += cub_parse_parameters(line, data);
		free (line);
	}
	if (parameters < 6)
	{
		close(fd);
		printf(ANSI_RED"Error:\nCheck paramaters in the map!"ANSI_DEF);
		return (CUB_ERROR);
	}
	if (cub_parse_map(data, data->map->map, fd) == CUB_ERROR)
		return (close(fd), CUB_ERROR);
	close (fd);
	return (ALL_FINE);
}


int main(int argc, char **argv)
{
	t_map	map;
	t_player player;
	t_data	data;
	int		i = -1;

	data.map = &map;
	data.player = &player;
	cub_parse(argv[1], &data);
	printf ("map.x: %d\nmap.y: %d\nplayer.pos.x: %f\nplayer.pos.y: %f\nplayer.angle: %f\n",
				map.x, map.y, player.pos.x, player.pos.y, player.angle);
	while (++i < map.y * map.x)
	{
			printf("%d", map.map[i]);
	}
}