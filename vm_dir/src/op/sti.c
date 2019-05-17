/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:21:10 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/22 07:04:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "visual.h"
#include "op.h"

static void	debug_mode(int reg, int *args, int addr, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "sti");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: r%d %d %d (pc %d)\n", "sti", reg, args[0], args[1]
				, addr);
}

int			sti(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	uint32_t	args[3];
	int			addr;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	if ((decode.tab[2].type == REG_CODE || decode.tab[2].type == DIR_CODE)
			&& decode.tab[1].type != BAD_REG && decode.tab[0].type == REG_CODE)
	{
		idx = -1;
		while (++idx < 3)
			store_multitype(&args[idx], decode, decode.tab[idx], 0);
		addr = ((int)args[1] + (int)args[2]) % IDX_MOD;
		write_in_arena(env, (uint8_t *)&args[0], 4, cur_process->pc + addr);
		if (env->visu == VISU_ON)
			write_ncurses((uint8_t *)args, cur_process->champ_id, 4
					, cur_process->pc + addr);
		if (env->debug == DEBUG_ON)
			debug_mode((int)decode.tab[0].value, (int *)args
					, cur_process->pc + addr, env->debug_lvl);
	}
	return (ret);
}
