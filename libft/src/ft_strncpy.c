/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 17:33:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/17 17:52:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	nlen;

	nlen = ft_strnlen(src, n);
	ft_memcpy(dest, src, nlen);
	if (n > nlen)
		ft_memset(dest + nlen, '\0', n - nlen);
	return (dest);
}
