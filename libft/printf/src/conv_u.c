/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 00:12:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 19:53:49 by gguichar         ###   ########.fr       */
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
		value /= 10;
	}
	return (size);
}

static void	pf_ulltoa(t_pf *pf, unsigned long long value)
{
	if (value >= 10)
		pf_ulltoa(pf, value / 10);
	buf_char(pf, (value % 10) + '0', 1);
}

void		pf_conv_u(t_pf *pf)
{
	unsigned long long	value;
	int					size;

	if (pf->flags & ZERO_FLAG && pf->precision >= 0)
		pf->flags &= ~ZERO_FLAG;
	value = pf_uvalue(pf);
	size = pf_ullsize(pf, value);
	pf->precision = ft_max(size, pf->precision);
	pf->w_field -= pf->precision;
	if (pf->flags & ZERO_FLAG)
	{
		pf->precision += ft_max(pf->w_field, 0);
		pf->w_field = 0;
	}
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	if (pf->precision > size)
		buf_char(pf, '0', pf->precision - size);
	if (size > 0)
		pf_ulltoa(pf, value);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
