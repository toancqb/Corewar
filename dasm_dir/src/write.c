/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 01:59:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 02:23:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <unistd.h>
#include "libft.h"
#include "dasm.h"

int		write_inst(t_data *data)
{
	uint32_t	idx;
	int			ret;

	idx = 0;
	while (idx < data->inst_len)
	{
		if ((ret = inst_manager(data, &data->inst[idx])) == 0)
			return (ERR_BADOPCODE);
		idx += ret;
	}
	return (ERR_NOERROR);
}

int		write_indir(t_data *data, uint8_t *byte)
{
	int	nb;

	if (byte + 2 > data->inst + data->inst_len)
		return (0);
	swap_bytes(byte, 2);
	nb = *((int16_t*)(byte));
	ft_putnbr_fd((int)nb, data->fd);
	return (2);
}

int		write_dire(t_data *data, uint8_t *byte, int direct)
{
	int	nb;

	if (byte + ((direct == 1) ? 2 : 4) > data->inst + data->inst_len)
		return (0);
	swap_bytes(byte, (direct == 1) ? 2 : 4);
	nb = (direct == 1) ? *((int16_t*)byte) : *((int*)byte);
	write(data->fd, "%", 1);
	ft_putnbr_fd(nb, data->fd);
	return ((direct == 1) ? 2 : 4);
}

int		write_reg(t_data *data, uint8_t *byte)
{
	int	nb;

	if (byte + 1 > data->inst + data->inst_len)
		return (0);
	nb = *((int8_t*)(byte));
	write(data->fd, "r", 1);
	ft_putnbr_fd(nb, data->fd);
	return (1);
}

uint8_t	write_arg(t_data *data, uint8_t *byte, t_op *op, uint8_t encoding)
{
	if ((encoding & 0xc0) == 0xc0)
		return (write_indir(data, byte));
	else if ((encoding & 0x80) == 0x80)
		return (write_dire(data, byte, op->direct));
	else if ((encoding & 0x40) == 0x40)
		return (write_reg(data, byte));
	return (0);
}
