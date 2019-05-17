/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:28:28 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/22 06:45:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int *args, int reg, int addr, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "ldi");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: %d %d r%d (pc %d)\n", "ldi", args[0], args[1], reg
				, addr);
}

int			ldi(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int				ret;
	t_decode		decode;
	uint32_t		args[2];
	int				addr;
	uint32_t		value;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE
			&& decode.tab[0].type != BAD_REG)
	{
		store_multitype(&args[0], decode, decode.tab[0], 0);
		store_multitype(&args[1], decode, decode.tab[1], 0);
		addr = cur_process->pc + ((int)args[0] + (int)args[1]) % IDX_MOD;
		fill_buff_from_arena(env, (uint8_t *)&value, 4, addr);
		swap_bytes((uint8_t *)&value, 4);
		cur_process->reg[(int)decode.tab[2].value - 1] = (uint64_t)value;
		if (env->debug == DEBUG_ON)
			debug_mode((int *)args, (int)decode.tab[2].value
					, addr, env->debug_lvl);
	}
	return (ret);
}
