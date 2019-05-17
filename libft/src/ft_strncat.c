/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 17:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/17 17:48:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	d_len;
	size_t	s_nlen;

	d_len = ft_strlen(dest);
	s_nlen = ft_strnlen(src, n);
	dest[d_len + s_nlen] = '\0';
	ft_memcpy(dest + d_len, src, s_nlen);
	return (dest);
}
