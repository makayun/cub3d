/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:19:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/13 09:33:46 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_check_input(int argc, char *filename)
{
	if (argc <= 1)
	{
		perror("Error\nPlease, choose any map and try again\n");
		return (CUB_ERROR);
	}
	else if (argc > 2)
	{
		perror("Error\nToo many arguments, try again!\n");
		return (CUB_ERROR);
	}
	else if (!ft_strnstr(filename, ".cub", ft_strlen(filename))
		|| !ft_strnstr(filename, "./", 2))
	{
		perror("Error\nWrong map name!\n");
		return (CUB_ERROR);
	}
	else
		return (ALL_FINE);
}