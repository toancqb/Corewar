/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:10:12 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 13:20:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_llsize(long long l)
{
	size_t	count;

	count = 0;
	if (l <= 0)
		count += 1;
	while (l != 0)
	{
		l /= 10;
		count++;
	}
	return (count);
}
