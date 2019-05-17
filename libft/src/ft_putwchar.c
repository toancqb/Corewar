/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 09:22:59 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 11:04:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putwchar(int c)
{
	char	bytes[4];
	int		index;

	index = 0;
	if (!(c >> 7))
		bytes[index++] = c;
	else if (c < 0x800)
	{
		bytes[index++] = (c >> 6) | 0xC0;
		bytes[index++] = (c & 0x3F) | 0x80;
	}
	else if (c < 0x10000)
	{
		bytes[index++] = (c >> 12) | 0xE0;
		bytes[index++] = ((c >> 6) & 0x3F) | 0x80;
		bytes[index++] = (c & 0x3F) | 0x80;
	}
	else
	{
		bytes[index++] = (c >> 18) | 0xF0;
		bytes[index++] = ((c >> 12) & 0x3F) | 0x80;
		bytes[index++] = ((c >> 6) & 0x3F) | 0x80;
		bytes[index++] = (c & 0x3F) | 0x80;
	}
	write(1, bytes, index);
}
