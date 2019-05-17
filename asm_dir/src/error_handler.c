/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 05:37:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "asm.h"

void	err_handler(t_error err_id)
{
	char	buf[255];

	ft_bzero(&buf, 255);
	ft_strcat(buf, "Terminated with error: ");
	if (err_id == ERR_BADFMT)
		ft_strcat(buf, "Bad format");
	else if (err_id == ERR_GNL)
		ft_strcat(buf, "Get next line error");
	else if (err_id == ERR_MALLOC)
		ft_strcat(buf, "Malloc error");
	else if (err_id == ERR_ERRNO)
		ft_strcat(buf, strerror(errno));
	else if (err_id == ERR_HEADER)
		ft_strcat(buf, "Header bad format");
	else if (err_id == ERR_NOINST)
		ft_strcat(buf, "Nothing after header");
	else if (err_id == ERR_DUPLABEL)
		ft_strcat(buf, "Duplicated label detected");
	else if (err_id == ERR_NOLABEL)
		ft_strcat(buf, "Label not found");
	else if (err_id == ERR_ARGNB)
		ft_strcat(buf, "Wrong argument number");
	write(2, ft_strcat(buf, "\n"), ft_strlen(buf) + 1);
}

t_error	err_print(char *str, t_error err_id)
{
	ft_dprintf(2, "\"%s\"\n", str);
	return (err_id);
}
