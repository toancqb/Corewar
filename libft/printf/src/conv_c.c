/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 10:26:35 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/10 10:15:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	pf_conv_c(t_pf *pf)
{
	pf->w_field -= 1;
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	if (!(pf->flags & L_MODIFIER))
		buf_char(pf, (char)va_arg(pf->ap, int), 1);
	else
		pf_write_utf8(pf, va_arg(pf->ap, wint_t));
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
