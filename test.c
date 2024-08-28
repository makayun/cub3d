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

int	cub_init_player_new(t_data *data, int x, int y, char dir)
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

int	cub_init_map_new(t_data *data, bool *map, char tmp_map[MAP_H_MAX][MAP_W_MAX])
{
	int		x;
	int		y;
	size_t	line_len;
	int		player_inited;

	player_inited = 0;
	y = 0;
	while (y < data->map->y)
	{
		line_len = ft_strlen(tmp_map[y]);
		x = 0;
		while (x < line_len)
		{
			player_inited += cub_init_player_new(data, x, y, tmp_map[y][x]);
			*(map++) = (tmp_map[y][x++] == '1');
		}
		while (x++ < data->map->x)
			*(map++) = 0;
		y++;
	}
	if (player_inited != 1)
		return (printf(T_RED"Error:\nCheck the player!\n"T_DEF), CUB_ERROR);
	// return (cub_check_map(tmp_map, data));
	return (ALL_FINE);
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
	return (cub_init_map_new(data, map->map, temp_map));
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

int main(int argc, char **argv)
{
	t_map	map;
	t_player player;
	t_data	data;
	int		i = 0;

	data.map = &map;
	data.player = &player;
	cub_parse(argv[1], &data);
	printf ("map.x: %d\nmap.y: %d\nplayer.pos.x: %f\nplayer.pos.y: %f\nplayer.angle: %f\n",
			map.x, map.y, player.pos.x, player.pos.y, player.angle);
	while (i < (data.map->y * data.map->x))
	{
		if (i % map.x == 0)
			printf("\n");
		printf("%d", map.map[i++]);
	}
}
