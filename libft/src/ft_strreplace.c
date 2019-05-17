/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 01:48:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/09/04 20:46:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_replace(char *dest, const char *src
	, const char *from, const char *to)
{
	size_t		from_len;
	size_t		to_len;
	const char	*offset;

	from_len = ft_strlen(from);
	to_len = ft_strlen(to);
	offset = src;
	while (*src != '\0')
	{
		if (!(offset = ft_strstr(offset, from)))
		{
			ft_strcpy(dest, src);
			break ;
		}
		ft_memcpy(dest, src, offset - src);
		dest += (offset - src);
		ft_memcpy(dest, to, to_len);
		dest += to_len;
		offset += from_len;
		src = offset;
	}
}

char		*ft_strreplace(const char *s, const char *from, const char *to)
{
	char		*dest;
	const char	*offset;
	size_t		found;
	size_t		new_len;

	if (s == NULL || from == NULL || to == NULL)
		return (NULL);
	offset = s;
	found = 0;
	while ((offset = ft_strstr(offset, from)) != NULL)
	{
		offset++;
		found++;
	}
	new_len = ft_strlen(s) + (ft_strlen(to) - ft_strlen(from)) * found;
	if (!(dest = (char *)malloc(sizeof(*dest) * (new_len + 1))))
		return (NULL);
	dest[new_len] = '\0';
	ft_replace(dest, s, from, to);
	return (dest);
}
