/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:50:06 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/28 14:21:29 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*cub_cut_whitespace(char *line)
{
	char	*end;

	if (!line || !*line)
		return (NULL);
	while (*line == ' ')
		line++;
	end = ft_strchr(line, ' ');
	if (end && *end)
		*end = 0;
	return (line);
}

inline void	cub_tool_coord_norm(int *x, int *y)
{
	*x *= (*x > 0);
	*y *= (*y > 0);
	*x += (*x >= WIN_WIDTH) * (WIN_WIDTH - *x - 1);
	*y += (*y >= WIN_HEIGHT) * (WIN_HEIGHT - *y - 1);
}

inline t_coord	cub_pos_to_coord(t_pos pos)
{
	t_coord	ret;

	ret.x = (int)(pos.x + 0.5);
	ret.y = (int)(pos.y + 0.5);
	return (ret);
}

inline float	cub_dist(t_pos a, t_pos b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

inline long	cub_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}
