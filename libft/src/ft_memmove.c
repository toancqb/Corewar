/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:03:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/06 09:22:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_memcpy_words_bw(t_lword *dest, const t_lword *src, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset + 4 * sizeof(*src) <= n)
	{
		dest -= 4;
		src -= 4;
		dest[0] = src[0];
		dest[1] = src[1];
		dest[2] = src[2];
		dest[3] = src[3];
		offset += 4 * sizeof(*src);
	}
	while (offset + sizeof(*src) <= n)
	{
		*(--dest) = *(--src);
		offset += sizeof(*src);
	}
	return (offset);
}

static void		*ft_memcpy_bw(void *dest, const void *src, size_t n)
{
	t_byte			*dst;
	const t_byte	*srcc;
	size_t			offset;

	dst = (t_byte *)dest + n;
	srcc = (const t_byte *)src + n;
	if (n > 2 * sizeof(t_lword)
		&& ((unsigned long)dst & (sizeof(t_lword) - 1))
		== ((unsigned long)srcc & (sizeof(t_lword) - 1)))
	{
		while (n > 0 && ((unsigned long)dst & (sizeof(t_lword) - 1)) != 0)
		{
			*(--dst) = *(--srcc);
			n--;
		}
		offset = ft_memcpy_words_bw((t_lword *)dst, (const t_lword *)srcc, n);
		dst -= offset;
		srcc -= offset;
		n -= offset;
	}
	while (n-- > 0)
		*(--dst) = *(--srcc);
	return (dest);
}

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	if (n > 0 && dest != src)
	{
		if (dest < src)
			ft_memcpy(dest, src, n);
		else
			ft_memcpy_bw(dest, src, n);
	}
	return (dest);
}
