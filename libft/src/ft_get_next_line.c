/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:44:15 by mmakagon          #+#    #+#             */
/*   Updated: 2024/06/03 12:57:29 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_next(char *buffer)
{
	char	*next;
	char	*tmp_buf;
	int		i;

	tmp_buf = ft_strchr(buffer, '\n');
	if (!tmp_buf++)
		return (free(buffer), NULL);
	next = malloc((ft_strlen(tmp_buf) + 1) * sizeof(char));
	if (!next)
		return (free(buffer), NULL);
	i = 0;
	while (*tmp_buf)
		next[i++] = *tmp_buf++;
	next[i] = '\0';
	free(buffer);
	return (next);
}

char	*gnl_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (line[i++] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_read(char *buffer, int fd)
{
	char	read_str[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, read_str, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		read_str[bytes_read] = '\0';
		temp = ft_strjoin(buffer, read_str);
		free (buffer);
		if (!temp || !*temp)
			return (free(temp), NULL);
		buffer = temp;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		*buffer[fd] = '\0';
	}
	buffer[fd] = gnl_read(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = gnl_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), NULL);
	buffer[fd] = gnl_next(buffer[fd]);
	return (line);
}
