/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:33:52 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 19:54:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static int	pf_ullsize(t_pf *pf, unsigned long long value)
{
	int	size;

	if (value == 0)
		return (pf->precision != 0);
	size = 0;
	while (value != 0)
	{
		size++;
		value /= 16;
	}
	return (size);
}

static void	pf_x_prepend(t_pf *pf, unsigned long long value, int size)
{
	if (value != 0 && pf->flags & HASH_FLAG)
		buf_write(pf, (pf->type == 'X' ? "0X" : "0x"), 2);
	if (pf->precision > size)
		buf_char(pf, '0', pf->precision - size);
}

static void	pf_ulltoa(t_pf *pf, unsigned long long value, const char *base)
{
	if (value >= 16)
		pf_ulltoa(pf, value / 16, base);
	buf_char(pf, base[value % 16], 1);
}

void		pf_conv_x(t_pf *pf)
{
	unsigned long long	value;
	int					size;

	if (pf->flags & ZERO_FLAG && pf->precision >= 0)
		pf->flags &= ~ZERO_FLAG;
	value = pf_uvalue(pf);
	size = pf_ullsize(pf, value);
	pf->precision = ft_max(size, pf->precision);
	pf->w_field -= pf->precision;
	if (value != 0 && pf->flags & HASH_FLAG)
		pf->w_field -= 2;
	if (pf->flags & ZERO_FLAG)
	{
		pf->precision += ft_max(pf->w_field, 0);
		pf->w_field = 0;
	}
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	pf_x_prepend(pf, value, size);
	if (size > 0)
		pf_ulltoa(pf, value
				, (pf->type == 'X' ? "0123456789ABCDEF" : "0123456789abcdef"));
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
