/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:39:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/22 04:11:07 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(t_decode decode, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "sub");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: r%d r%d r%d\n", "sub"
				, (int)decode.tab[0].value
				, (int)decode.tab[1].value
				, (int)decode.tab[2].value);
}

int			sub(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	int			value;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	idx = 0;
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE)
			return (ret);
		idx++;
	}
	value = (int)cur_process->reg[(int)decode.tab[0].value - 1];
	value -= (int)cur_process->reg[(int)decode.tab[1].value - 1];
	cur_process->reg[(int)decode.tab[2].value - 1] = (uint32_t)value;
	cur_process->carry = (value == 0);
	if (env->debug == DEBUG_ON)
		debug_mode(decode, env->debug_lvl);
	return (ret);
}
