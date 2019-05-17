/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 02:02:00 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 03:57:21 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <unistd.h>
#include "libft.h"
#include "dasm.h"

extern t_op	g_op_tab[];

int		manage_argv(t_data *data, t_op *op, uint8_t *byte)
{
	uint8_t	encoding;
	uint8_t	*ref;
	uint8_t	pad;
	int		idx;

	ref = byte;
	if (op->encoding == 1)
	{
		encoding = *byte++;
		idx = -1;
		while (encoding > 0 && ++idx < op->argc)
		{
			if ((pad = write_arg(data, byte, op, encoding)) == 0)
				return (-1);
			if ((encoding <<= 2) > 0)
				write(data->fd, ", ", 2);
			byte += pad;
		}
	}
	else if ((pad = write_dire(data, byte, op->direct)) == 0)
		return (-1);
	write(data->fd, "\n", 1);
	byte += (op->encoding == 1) ? 0 : pad;
	return (byte - ref);
}

int		inst_manager(t_data *data, uint8_t *byte)
{
	t_op	op;

	op = find_op(byte);
	if (op.opcode == 0)
		return (0);
	write(data->fd, op.name, ft_strlen(op.name));
	write(data->fd, " ", 1);
	byte += 1;
	return (manage_argv(data, &op, byte) + 1);
}

t_error	get_inst(t_data *data, int fd)
{
	uint8_t	*tmp;
	int		ret;

	ft_bzero(data->buf, BUFF_SIZE + 1);
	while ((ret = read(fd, data->buf, BUFF_SIZE + 1)))
	{
		if (data->inst == NULL)
		{
			if ((data->inst = ft_memdup((uint8_t*)data->buf, ret)) == NULL)
				return (ERR_ERRNO);
			data->inst_len = ret;
		}
		else
		{
			tmp = data->inst;
			if ((data->inst = ft_memjoin(data->inst,
							(uint8_t*)data->buf, data->inst_len, ret)) == NULL)
				return (ERR_ERRNO);
			data->inst_len += ret;
			ft_memdel((void **)&tmp);
		}
		ft_bzero(data->buf, BUFF_SIZE + 1);
	}
	return (ERR_NOERROR);
}

t_op	find_op(uint8_t *byte)
{
	int	idx;

	idx = 0;
	while (idx < 16)
	{
		if (g_op_tab[idx].opcode == *byte)
			return (g_op_tab[idx]);
		idx += 1;
	}
	return (g_op_tab[idx]);
}
