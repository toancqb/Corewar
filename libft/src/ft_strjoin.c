/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:57:26 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 23:54:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = (s1 == NULL) ? 0 : ft_strlen(s1);
	s2_len = (s2 == NULL) ? 0 : ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (s1_len + s2_len + 1))))
		return (NULL);
	if (s1_len > 0)
		ft_memcpy(str, s1, s1_len);
	if (s2_len > 0)
		ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}
