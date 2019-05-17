/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:02:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/17 00:03:58 by gguichar         ###   ########.fr       */
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

char		*ft_ulltoa_base(unsigned long long n, int base)
{
	unsigned long long	value;
	int					count;
	char				*str;

	if (base < 2 || base > 36)
		return (NULL);
	value = n;
	count = n == 0;
	while (value != 0)
	{
		value /= base;
		count++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	value = n;
	while (count > 0)
	{
		count--;
		str[count] = ft_base_char(value % base);
		value /= base;
	}
	return (str);
}
