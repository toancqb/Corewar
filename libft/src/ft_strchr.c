/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 01:54:05 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/08 03:17:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == 0)
		return (char *)(s + ft_strlen(s));
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (char *)(s);
		s++;
	}
	return (NULL);
}
