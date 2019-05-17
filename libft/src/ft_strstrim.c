/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 21:09:04 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/10 03:58:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstrim(char const *s, char const *spaces)
{
	size_t	len;

	if (s == NULL || spaces == NULL)
		return (NULL);
	while (*s != '\0' && ft_strchr(spaces, *s) != NULL)
		s++;
	len = ft_strlen(s);
	while (len > 0 && ft_strchr(spaces, s[len - 1]) != NULL)
		len--;
	return (ft_strsub(s, 0, len));
}
