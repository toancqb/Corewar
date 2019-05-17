/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 02:15:36 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 04:47:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "dasm.h"

void	err_handler(t_data *data, t_error id)
{
	if (id == ERR_NOERROR)
		ft_printf("Desassembled to %s\n", data->filename);
	if (id == ERR_ERRNO)
		ft_dprintf(2, "Error: %s\n", strerror(errno));
	if (id == ERR_SIZEHEADER)
		ft_dprintf(2, "Error: Bad header size\n");
	if (id == ERR_PROGSIZE)
		ft_dprintf(2, "Error: Bad program size\n");
	if (id == ERR_BADTYPE)
		ft_dprintf(2, "Error: Bad argument type\n");
	if (id == ERR_NBARG)
		ft_dprintf(2, "Error: Bad argument number\n");
	if (id == ERR_BADOPCODE)
		ft_dprintf(2, "Error: Unrecognized opcode/encoding byte\n");
	ft_strdel(&data->filename);
}
