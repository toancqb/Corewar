/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:12:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 03:49:46 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int param, int pc, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "fork");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: %d (pc %d)\n", "fork", param, pc);
}

int			ft_fork(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*node;
	t_process	*process;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	node = ft_lstnew(cur_process, sizeof(t_process));
	if (node == NULL)
		return (-1);
	process = (t_process *)node->content;
	process->queued_op = 0;
	increase_pc(process, (int)decode.tab[0].value % IDX_MOD);
	ft_lstadd(&env->process_lst, node);
	if (env->debug == DEBUG_ON)
		debug_mode(decode.tab[0].value, process->pc, env->debug_lvl);
	return (ret);
}
