/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:48:51 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/29 00:55:00 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ret;
	ssize_t		len;
	ssize_t		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	if (s1)
		while (i < len && *s1)
			ret[i++] = *s1++;
	if (s2)
		while (i < len && *s2)
			ret[i++] = *s2++;
	ret[i] = '\0';
	return (ret);
}
