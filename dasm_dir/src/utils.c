/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 02:05:07 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 02:10:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <stdlib.h>
#include "libft.h"

uint8_t	*ft_memjoin(uint8_t *s1, uint8_t *s2, int s1_len, int s2_len)
{
	uint8_t	*new;
	int		total_len;
	int		idx;

	total_len = s1_len + s2_len;
	new = (uint8_t *)malloc(sizeof(uint8_t) * (total_len));
	if (new == NULL)
		return (NULL);
	idx = 0;
	total_len = (s1_len >= s2_len) ? s1_len : s2_len;
	while (idx < total_len)
	{
		if (idx < s1_len)
			new[idx] = s1[idx];
		if (idx < s2_len)
			new[s1_len + idx] = s2[idx];
		idx += 1;
	}
	return (new);
}

uint8_t	*ft_memdup(uint8_t *src, int len)
{
	uint8_t	*new;

	new = (uint8_t *)malloc(sizeof(uint8_t) * len);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, src, len);
	return (new);
}

void	swap_bytes(uint8_t *str, int size)
{
	uint8_t	tmp;
	int		i;

	i = 0;
	while (i < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
		i++;
	}
}
