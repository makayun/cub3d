/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:19:00 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/08/26 00:35:46 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_check_input(int argc, char *filename)
{
	if (argc <= 1)
	{
		perror(ANSI_RED"Error:\nPlease, choose a map and try again\n"ANSI_DEF);
		return (CUB_ERROR);
	}
	else if (argc > 2)
	{
		perror(ANSI_RED"Error:\nToo many arguments, try again!\n"ANSI_DEF);
		return (CUB_ERROR);
	}
	else if (!ft_strnstr(filename, ".cub", ft_strlen(filename))
		|| !ft_strnstr(filename, "./", 2))
	{
		perror(ANSI_RED"Error:\nWrong map filename!\n"ANSI_DEF);
		return (CUB_ERROR);
	}
	else
		return (ALL_FINE);
}
