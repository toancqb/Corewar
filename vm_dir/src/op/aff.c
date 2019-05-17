/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 03:54:14 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/22 03:43:47 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int r1, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "aff");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: r%d\n", "aff", r1);
}

int			aff(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			reg;
	char		c;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), REG_DIR) + 2;
	if (decode.tab[0].type == REG_CODE)
	{
		reg = (int)decode.tab[0].value;
		c = ((int)cur_process->reg[reg - 1]) % 256;
		ft_putchar(c);
		if (env->debug == DEBUG_ON)
			debug_mode((int)decode.tab[0].value, env->debug_lvl);
	}
	return (ret);
}
