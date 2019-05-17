/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:52:31 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/22 17:18:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_words_len(char **tab, size_t glue_len)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	if (i > 1)
		len += glue_len * (i - 1);
	return (len);
}

static void		ft_words_join(char *dest
	, char **src, const char *glue, size_t glue_len)
{
	size_t	i;
	size_t	w_len;

	i = 0;
	while (src[i] != NULL)
	{
		if (i > 0)
		{
			ft_memcpy(dest, glue, glue_len);
			dest += glue_len;
		}
		w_len = ft_strlen(src[i]);
		ft_memcpy(dest, src[i], w_len);
		dest += w_len;
		i++;
	}
}

char			*ft_join(char **tab, const char *glue)
{
	size_t	glue_len;
	size_t	total_len;
	char	*str;

	glue_len = ft_strlen(glue);
	total_len = ft_words_len(tab, glue_len);
	if (!(str = (char *)malloc(sizeof(*str) * (total_len + 1))))
		return (NULL);
	str[total_len] = '\0';
	ft_words_join(str, tab, glue, glue_len);
	return (str);
}
