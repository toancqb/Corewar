/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_managers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 04:42:53 by qtran             #+#    #+#             */
/*   Updated: 2019/02/23 05:40:53 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <inttypes.h>
#include "asm.h"

void		manage_ind(t_filter *arg, int fd)
{
	uint16_t	two_bytes;

	if (arg->size == 4)
	{
		swap_bytes((uint8_t*)&arg->value, 4);
		write(fd, &arg->value, 4);
	}
	else
	{
		two_bytes = (uint16_t)arg->value;
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
}

void		manage_dir(t_filter *inst, t_filter *arg, int fd)
{
	uint16_t	two_bytes;

	if (inst->op.direct == 1 || arg->size == 2)
	{
		two_bytes = (uint16_t)arg->value;
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
	else
	{
		swap_bytes((uint8_t*)&arg->value, 4);
		write(fd, &arg->value, 4);
	}
}

void		manage_label(t_filter *inst, t_filter *arg, t_filter *label, int fd)
{
	uint16_t	two_bytes;
	uint32_t	four_bytes;

	if (inst->op.direct == 1 || arg->size == 2)
	{
		two_bytes = (uint16_t)(label->index - inst->index);
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
	else
	{
		four_bytes = (uint32_t)(label->index - inst->index);
		swap_bytes((uint8_t*)&four_bytes, 4);
		write(fd, &four_bytes, 4);
	}
}

int			manage_inst(t_filter *inst, t_data *data, int fd)
{
	t_filter	*arg;
	t_filter	*label;
	int			idx;

	arg = inst + 1;
	idx = 0;
	write(fd, &inst->op.opcode, 1);
	if (inst->op.encoding == 1)
		write_encoding_byte(&inst->op, fd);
	while (idx < inst->op.argc && arg < data->filter + data->f_size)
	{
		if ((label = is_label(arg->op.name, data->label_lst.head)) != NULL)
			manage_label(inst, arg, label, fd);
		else if (arg->label == LX_INDIR)
			manage_ind(arg, fd);
		else if (arg->label == LX_REG)
			write(fd, &arg->value, 1);
		else if (arg->label == LX_DIRE)
			manage_dir(inst, arg, fd);
		arg += 1;
		idx += 1;
	}
	if (idx < inst->op.argc && arg >= data->filter + data->f_size)
		return (0);
	return (inst->op.argc);
}

int			manage_filter(t_filter *elem, t_data *data, int fd)
{
	if (elem->label == LX_INST)
		return (manage_inst(elem, data, fd));
	return (1);
}
