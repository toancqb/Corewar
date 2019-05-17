/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 20:39:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 16:22:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "printf.h"

int	ft_printf(const char *format, ...)
{
	t_pf	pf;
	char	buf[PRINTF_BUF];

	if (format == NULL)
		return (-1);
	pf.fd = 1;
	pf.buf = buf;
	pf.buf_off = 0;
	pf.buf_write = 0;
	pf.ret = NULL;
	va_start(pf.ap, format);
	pf_parse(&pf, format);
	va_end(pf.ap);
	pf.buf_write += write(pf.fd, pf.buf, pf.buf_off);
	return (pf.buf_write);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_pf	pf;
	char	buf[PRINTF_BUF];

	if (fd < 0 || format == NULL)
		return (-1);
	pf.fd = fd;
	pf.buf = buf;
	pf.buf_off = 0;
	pf.buf_write = 0;
	pf.ret = NULL;
	va_start(pf.ap, format);
	pf_parse(&pf, format);
	va_end(pf.ap);
	pf.buf_write += write(pf.fd, pf.buf, pf.buf_off);
	return (pf.buf_write);
}

int	ft_asprintf(char **ret, const char *format, ...)
{
	t_pf	pf;

	if (ret == NULL || format == NULL
			|| !(pf.buf = (char *)malloc(PRINTF_BUF + 1)))
		return (-1);
	pf.fd = -1;
	pf.buf_off = 0;
	pf.buf_write = 0;
	pf.ret = ret;
	va_start(pf.ap, format);
	pf_parse(&pf, format);
	va_end(pf.ap);
	pf.buf_write += pf.buf_off;
	pf.buf[pf.buf_off] = '\0';
	*ret = pf.buf;
	return (pf.buf_write);
}
