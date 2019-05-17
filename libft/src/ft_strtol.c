/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:59:06 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/06 09:34:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int		ft_guess_base(const char **str, int base)
{
	if (base != 0 && (base < 2 || base > 36))
		return (0);
	if ((base == 0 || base == 16)
		&& ((*str)[0] == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
		&& (((*str)[2] >= '0' && (*str)[2] <= '9')
			|| ((*str)[2] >= 'A' && (*str)[2] <= 'F')
			|| ((*str)[2] >= 'a' && (*str)[2] <= 'f')))
	{
		(*str) += 2;
		return (16);
	}
	if (base == 0)
		return (**str == '0' ? 8 : 10);
	return (base);
}

static int		ft_base_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (42);
}

static size_t	ft_skip_spaces(const char *nptr, int *neg)
{
	size_t	i;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	*neg = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		*neg = nptr[i] == '-';
		i++;
	}
	return (i);
}

static long int	ft_fix_neg(long int result, int neg)
{
	if (result < 0)
		return (neg ? LONG_MIN : LONG_MAX);
	else if (neg)
		return (result * -1);
	return (result);
}

long int		ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*str;
	long int	result;
	int			neg;
	int			found;
	int			current;

	str = nptr + ft_skip_spaces(nptr, &neg);
	result = 0;
	found = 0;
	if ((base = ft_guess_base(&str, base)) > 0)
	{
		while ((current = ft_base_val(*str)) < base)
		{
			found = 1;
			if ((result = current + (result * base)) < 0)
				break ;
			str++;
		}
		result = ft_fix_neg(result, neg);
	}
	if (endptr != NULL)
		*endptr = (char *)(found ? str : nptr);
	return (result);
}
