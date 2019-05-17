/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 20:35:15 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/17 17:48:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	nlen;
	char	*str;

	nlen = ft_strnlen(s, n);
	if ((str = (char *)malloc(sizeof(*str) * (nlen + 1))) == NULL)
		return (NULL);
	str[nlen] = '\0';
	ft_memcpy(str, s, nlen);
	return (str);
}
