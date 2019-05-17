/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:22:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 01:37:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

void	fill_decode(t_env *env, t_process *process, t_decode *decode
		, int nb_arg)
{
	ft_memset(decode, 0, sizeof(t_decode));
	decode->env = env;
	decode->process = process;
	decode->max_args = nb_arg;
}

void	store_multitype(uint32_t *buffer, t_decode decode, t_arg arg
		, int is_long)
{
	int	addr;

	if (arg.type == REG_CODE)
		*buffer = decode.process->reg[(int)arg.value - 1];
	else if (arg.type == DIR_CODE)
		*buffer = arg.value;
	else if (arg.type == IND_CODE)
	{
		addr = decode.process->pc;
		if (is_long)
			addr += (int)arg.value;
		else
			addr += (int)arg.value % IDX_MOD;
		fill_buff_from_arena(decode.env, (uint8_t *)buffer, 4, addr);
		swap_bytes((uint8_t *)buffer, 4);
	}
}
