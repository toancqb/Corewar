/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:03:44 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/30 01:54:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	t_byte	*chr;

	chr = (t_byte *)ft_memchr(src, c, n);
	if (chr != NULL)
	{
		n = (chr - (t_byte *)src) + 1;
		ft_memcpy(dest, src, n);
		return (void *)((t_byte *)dest + n);
	}
	ft_memcpy(dest, src, n);
	return (NULL);
}
