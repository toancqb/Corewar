/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 03:38:20 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/07 16:31:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	if (d_len >= size)
		return (s_len + size);
	size = ft_min(s_len, size - d_len - 1);
	if (size > 0)
		ft_memcpy(dest + d_len, src, size);
	dest[d_len + size] = '\0';
	return (s_len + d_len);
}
