/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:24:27 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/06 09:23:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_memcmp_words(const t_lword *s1, const t_lword *s2, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset + 4 * sizeof(*s1) <= n)
	{
		if (s1[0] != s2[0])
			return (offset);
		if (s1[1] != s2[1])
			return (offset + sizeof(*s1));
		if (s1[2] != s2[2])
			return (offset + 2 * sizeof(*s1));
		if (s1[3] != s2[3])
			return (offset + 3 * sizeof(*s1));
		s1 += 4;
		s2 += 4;
		offset += 4 * sizeof(*s1);
	}
	while (offset + sizeof(*s1) <= n)
	{
		if (*s1++ != *s2++)
			return (offset);
		offset += sizeof(*s1);
	}
	return (offset);
}

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_byte	*p1;
	const t_byte	*p2;
	size_t			offset;
	int				diff;

	p1 = (t_byte *)s1;
	p2 = (t_byte *)s2;
	diff = 0;
	if (n > 2 * sizeof(t_lword) && ((unsigned long)p1 & (sizeof(t_lword) - 1))
		== ((unsigned long)p2 & (sizeof(t_lword) - 1)))
	{
		while (n > 0 && ((unsigned long)p1 & (sizeof(t_lword) - 1)) != 0)
		{
			if ((diff = *p1++ - *p2++) != 0)
				return (diff);
			n--;
		}
		offset = ft_memcmp_words((const t_lword *)p1, (const t_lword *)p2, n);
		p1 += offset;
		p2 += offset;
		n -= offset;
	}
	while (n-- > 0 && (diff = *p1++ - *p2++) == 0)
		continue ;
	return (diff);
}
