/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:03:37 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/22 22:29:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_memcpy_words(t_lword *dest, const t_lword *src, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset + 4 * sizeof(*src) <= n)
	{
		dest[0] = src[0];
		dest[1] = src[1];
		dest[2] = src[2];
		dest[3] = src[3];
		dest += 4;
		src += 4;
		offset += 4 * sizeof(*src);
	}
	while (offset + sizeof(*src) <= n)
	{
		*dest++ = *src++;
		offset += sizeof(*src);
	}
	return (offset);
}

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte			*dst;
	const t_byte	*srcc;
	size_t			offset;

	dst = (t_byte *)dest;
	srcc = (const t_byte *)src;
	if (n > 2 * sizeof(t_lword)
		&& ((unsigned long)dst & (sizeof(t_lword) - 1))
		== ((unsigned long)srcc & (sizeof(t_lword) - 1)))
	{
		while (n > 0 && ((unsigned long)dst & (sizeof(t_lword) - 1)) != 0)
		{
			*dst++ = *srcc++;
			n--;
		}
		offset = ft_memcpy_words((t_lword *)dst, (const t_lword *)srcc, n);
		dst += offset;
		srcc += offset;
		n -= offset;
	}
	while (n-- > 0)
		*dst++ = *srcc++;
	return (dest);
}
