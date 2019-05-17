/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:14:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/10 10:11:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

long long			pf_value(t_pf *pf)
{
	if (pf->flags & HH_MODIFIER)
		return (char)(va_arg(pf->ap, int));
	else if (pf->flags & H_MODIFIER)
		return (short)(va_arg(pf->ap, int));
	else if (pf->flags & L_MODIFIER)
		return (va_arg(pf->ap, long));
	else if (pf->flags & LL_MODIFIER)
		return (va_arg(pf->ap, long long));
	else if (pf->flags & J_MODIFIER)
		return (va_arg(pf->ap, intmax_t));
	else if (pf->flags & Z_MODIFIER)
		return (va_arg(pf->ap, ssize_t));
	else
		return (va_arg(pf->ap, int));
}

unsigned long long	pf_uvalue(t_pf *pf)
{
	if (pf->flags & HH_MODIFIER)
		return (unsigned char)(va_arg(pf->ap, unsigned int));
	else if (pf->flags & H_MODIFIER)
		return (unsigned short)(va_arg(pf->ap, unsigned int));
	else if (pf->flags & L_MODIFIER)
		return (va_arg(pf->ap, unsigned long));
	else if (pf->flags & LL_MODIFIER)
		return (va_arg(pf->ap, unsigned long long));
	else if (pf->flags & J_MODIFIER)
		return (va_arg(pf->ap, uintmax_t));
	else if (pf->flags & Z_MODIFIER)
		return (va_arg(pf->ap, size_t));
	else
		return (va_arg(pf->ap, unsigned int));
}

void				pf_write_utf8(t_pf *pf, wint_t c)
{
	if (c < (1 << 7))
		buf_char(pf, c, 1);
	else if (c < (1 << 11))
	{
		buf_char(pf, (c >> 6) | 0xC0, 1);
		buf_char(pf, (c & 0x3F) | 0x80, 1);
	}
	else if (c < (1 << 16))
	{
		buf_char(pf, (c >> 12) | 0xE0, 1);
		buf_char(pf, ((c >> 6) & 0x3F) | 0x80, 1);
		buf_char(pf, (c & 0x3F) | 0x80, 1);
	}
	else if (c < (1 << 21))
	{
		buf_char(pf, (c >> 18) | 0xF0, 1);
		buf_char(pf, ((c >> 12) & 0x3F) | 0x80, 1);
		buf_char(pf, ((c >> 6) & 0x3F) | 0x80, 1);
		buf_char(pf, (c & 0x3F) | 0x80, 1);
	}
}
