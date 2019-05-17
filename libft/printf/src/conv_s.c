/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:37:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/10 13:54:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "printf.h"

static size_t	pf_strlen(t_pf *pf, char *str)
{
	if (!(pf->flags & L_MODIFIER))
		return (ft_strlen(str));
	else
		return (ft_wstrlen((wchar_t *)str));
}

static void		pf_write_wstr(t_pf *pf, wchar_t *wstr)
{
	while (*wstr != L'\0')
	{
		pf->precision -= ft_wcharlen(*wstr);
		if (pf->precision < 0)
			break ;
		pf_write_utf8(pf, *wstr);
		wstr++;
	}
}

void			pf_conv_s(t_pf *pf)
{
	char	*str;

	if (!(str = va_arg(pf->ap, char *)))
	{
		str = "(null)";
		pf->flags &= ~L_MODIFIER;
	}
	if (pf->precision < 0)
		pf->precision = pf_strlen(pf, str);
	else
		pf->precision = ft_min(pf->precision, pf_strlen(pf, str));
	if (pf->w_field > 0)
		pf->w_field -= pf->precision;
	if (pf->w_field > 0 && !(pf->flags & MINUS_FLAG))
		buf_pad(pf);
	if (!(pf->flags & L_MODIFIER))
		buf_write(pf, str, pf->precision);
	else
		pf_write_wstr(pf, (wchar_t *)str);
	if (pf->w_field > 0 && pf->flags & MINUS_FLAG)
		buf_pad(pf);
}
