/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 00:12:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 19:44:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static int	pf_llsize(t_pf *pf, long long value)
{
	int	size;

	if (value == 0)
		return (pf->precision != 0);
	size = 0;
	while (value != 0)
	{
		size++;
		value /= 10;
	}
	return (size);
}

static void	pf_di_prepend(t_pf *pf, long long value, int size)
{
	if (value < 0)
		buf_char(pf, '-', 1);
	else if (pf->flags & SPACE_FLAG || pf->flags & PLUS_FLAG)
		buf_char(pf, pf->flags & PLUS_FLAG ? '+' : ' ', 1);
	if (pf->precision > size)
		buf_char(pf, '0', pf->precision - size);
}

static void	pf_lltoa(t_pf *pf, long long value)
{
	if (value >= 10)
		pf_lltoa(pf, value / 10);
	else if (value <= -10)
		pf_lltoa(pf, -(value / 10));
	buf_char(pf, ft_abs(value % 10) + '0', 1);
}

void		pf_conv_di(t_pf *pf)
{
	long long	value;
	int			size;

	if (pf->flags & ZERO_FLAG && pf->precision >= 0)
		pf->flags &= ~ZERO_FLAG;
	value = pf_value(pf);
	size = pf_llsize(pf, value);
	pf->precision = ft_max(size, pf->precision);
	pf->w_field -= pf->precision;
	if (value < 0 || pf->flags & SPACE_FLAG || pf->flags & PLUS_FLAG)
		pf->w_field--;
	if (pf->flags & ZERO_FLAG)
	{
		pf->precision += ft_max(pf->w_field, 0);
		pf->w_field = 0;
	}
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	pf_di_prepend(pf, value, size);
	if (size > 0)
		pf_lltoa(pf, value);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
