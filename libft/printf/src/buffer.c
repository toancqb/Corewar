/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:01:44 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/10 12:57:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "printf.h"

void	buf_write(t_pf *pf, const char *buf, size_t nbytes)
{
	size_t	off;

	if (pf->buf_off + nbytes <= PRINTF_BUF)
	{
		ft_memcpy(pf->buf + pf->buf_off, buf, nbytes);
		pf->buf_off += nbytes;
	}
	else
	{
		off = PRINTF_BUF - pf->buf_off;
		buf_write(pf, buf, off);
		if (pf->ret == NULL)
			pf->buf_write += write(pf->fd, pf->buf, PRINTF_BUF);
		else
			pf->buf_write += PRINTF_BUF;
		pf->buf_off = 0;
		buf_write(pf, buf + off, nbytes - off);
	}
}

void	buf_pad(t_pf *pf)
{
	char	c;

	c = pf->flags & ZERO_FLAG ? '0' : ' ';
	buf_char(pf, c, pf->w_field);
}

void	buf_char(t_pf *pf, char c, size_t nbytes)
{
	while (nbytes > 0)
	{
		buf_write(pf, &c, 1);
		nbytes--;
	}
}
