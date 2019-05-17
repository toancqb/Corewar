/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:03:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/09/03 02:02:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_lword	ft_setup_word(int c)
{
	t_lword	value;

	value = c | (c << 8);
	value |= value << 16;
	if (sizeof(value) > 4)
		value |= (value << 16) << 16;
	return (value);
}

static size_t	ft_memset_words(t_lword *src, t_lword value, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset + 4 * sizeof(value) <= n)
	{
		src[0] = value;
		src[1] = value;
		src[2] = value;
		src[3] = value;
		src += 4;
		offset += 4 * sizeof(value);
	}
	while (offset + sizeof(value) <= n)
	{
		*src++ = value;
		offset += sizeof(value);
	}
	return (offset);
}

void			*ft_memset(void *s, int c, size_t n)
{
	t_byte	*src;
	size_t	offset;

	c = (t_byte)c;
	src = (t_byte *)s;
	if (n > 2 * sizeof(t_lword))
	{
		while (n > 0 && ((unsigned long)src & (sizeof(t_lword) - 1)) != 0)
		{
			*src++ = c;
			n--;
		}
		offset = ft_memset_words((t_lword *)src, ft_setup_word(c), n);
		src += offset;
		n -= offset;
	}
	while (n-- > 0)
		*src++ = c;
	return (s);
}
