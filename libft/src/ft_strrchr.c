/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:21:28 by mmakagon          #+#    #+#             */
/*   Updated: 2024/08/26 21:45:23 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char				*newchar;
	const unsigned char	ch = (char)c;

	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)(ft_strlen(s) + s));
	if (s[0] == '\0')
		return (NULL);
	newchar = NULL;
	while (*s != '\0')
	{
		if (*s == ch)
			newchar = (char *)s;
		s++;
	}
	return ((char *)newchar);
}
