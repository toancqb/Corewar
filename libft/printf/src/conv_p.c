/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:15:29 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 20:51:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "printf.h"

static int	pf_ptrsize(t_pf *pf, intptr_t value)
{
	int	size;

	if (pf->precision == 0 && value == 0)
		return (0);
	size = (value == 0);
	while (value != 0)
	{
		size++;
		value /= 16;
	}
	return (size);
}

static void	pf_ptrtoa(t_pf *pf, intptr_t value)
{
	if (value >= 16)
		pf_ptrtoa(pf, value / 16);
	else if (value <= -16)
		pf_ptrtoa(pf, -(value / 16));
	buf_char(pf, "0123456789abcdef"[ft_abs(value % 16)], 1);
}

void		pf_conv_p(t_pf *pf)
{
	intptr_t	ptr;
	int			size;

	ptr = va_arg(pf->ap, intptr_t);
	size = pf_ptrsize(pf, ptr);
	pf->precision = ft_max(size, pf->precision);
	pf->w_field -= (pf->precision + 2);
	if (pf->flags & ZERO_FLAG)
	{
		pf->precision += ft_max(pf->w_field, 0);
		pf->w_field = 0;
	}
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	buf_write(pf, "0x", 2);
	if (pf->precision > size)
		buf_char(pf, '0', pf->precision - size);
	if (size > 0)
		pf_ptrtoa(pf, ptr);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
