/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 03:10:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/16 09:32:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	ft_base_char(int n)
{
	if (n < 10)
		return (n + '0');
	return (n - 10 + 'A');
}

char		*ft_itoa_base(int n, int base)
{
	unsigned int	value;
	int				count;
	char			*str;

	if (base < 2 || base > 36)
		return (NULL);
	value = (n < 0) ? -n : n;
	count = (n == 0 || (n < 0 && base == 10));
	while (value != 0)
	{
		value /= base;
		count++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	value = (n < 0) ? -n : n;
	while (--count > 0)
	{
		str[count] = ft_base_char(value % base);
		value /= base;
	}
	*str = (n < 0 && base == 10 ? '-' : ft_base_char(value));
	return (str);
}
