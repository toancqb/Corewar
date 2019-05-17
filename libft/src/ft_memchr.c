/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:16:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/09/03 01:57:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_memory_offset(const t_byte *s, int c, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset < n && ((unsigned long)s & (sizeof(t_lword) - 1)) != 0)
	{
		if (*s++ == c)
			return (offset);
		offset++;
	}
	return (offset);
}

static size_t	ft_memchr_words(const t_lword *s, int c, size_t n)
{
	t_lword	magic_bits;
	t_lword	charmask;
	t_lword	value;
	size_t	offset;

	magic_bits = 0x01010101;
	charmask = c | (c << 8);
	charmask |= charmask << 16;
	if (sizeof(value) > 4)
	{
		magic_bits |= (magic_bits << 16) << 16;
		charmask |= (charmask << 16) << 16;
	}
	offset = 0;
	while (offset + sizeof(value) <= n)
	{
		value = (*s++) ^ charmask;
		if ((((value - magic_bits) & ~value) & (magic_bits << 7)) != 0)
			return (offset);
		offset += sizeof(value);
	}
	return (offset);
}

void			*ft_memchr(const void *s, int c, size_t n)
{
	const t_byte	*src;
	size_t			offset;

	c = (t_byte)c;
	src = (const t_byte *)s;
	if (n > 2 * sizeof(t_lword))
	{
		offset = ft_memory_offset(src, c, n);
		n -= offset;
		src += offset;
		if (*src == c)
			return (void *)(src);
		offset = ft_memchr_words((const t_lword *)src, c, n);
		n -= offset;
		src += offset;
	}
	while (n-- > 0)
	{
		if (*src == c)
			return (void *)(src);
		src++;
	}
	return (NULL);
}
