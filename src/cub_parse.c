/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:14:33 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/14 11:32:27 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_parse(char **argv, t_data *data)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == CUB_ERROR)
		return (CUB_ERROR);
	(void)data;
	close (fd);
	return (ALL_FINE);
}