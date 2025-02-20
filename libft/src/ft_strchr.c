/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:03:36 by mmakagon          #+#    #+#             */
/*   Updated: 2024/08/26 21:36:22 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (!s || !*s)
		return (NULL);
	ch = (char)c;
	while (*s != ch && *s != '\0')
		s++;
	if (*s == ch)
		return ((char *)s);
	else
		return (NULL);
}
