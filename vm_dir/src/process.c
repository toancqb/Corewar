/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 22:53:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:57:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

const t_op	g_op[] = {
	{live, 10},
	{ld, 5},
	{st, 5},
	{add, 10},
	{sub, 10},
	{ft_and, 6},
	{ft_or, 6},
	{ft_xor, 6},
	{zjmp, 20},
	{ldi, 25},
	{sti, 25},
	{ft_fork, 800},
	{lld, 10},
	{lldi, 50},
	{ft_lfork, 1000},
	{aff, 2}
};

t_process	*create_process(t_env *env, t_champ *champ)
{
	t_process	process;
	t_list		*node;

	ft_memset(&process, 0, sizeof(t_process));
	node = ft_lstnew(&process, sizeof(t_process));
	if (node == NULL)
		return (NULL);
	((t_process *)node->content)->champ_id = champ->id;
	((t_process *)node->content)->reg[0] = champ->id;
	ft_lstadd(&env->process_lst, node);
	return ((t_process *)node->content);
}

static void	exec_inst(t_env *env, t_process *process)
{
	int		opcode;
	int		ret;
	uint8_t	inst[MAX_INST_SIZE];

	opcode = process->queued_op;
	if (opcode < 1 || opcode > 16)
		increase_pc(process, 1);
	else
	{
		opcode -= 1;
		fill_buff_from_arena(env, inst, MAX_INST_SIZE, process->pc);
		ret = g_op[opcode].fn(env, process, inst);
		if (env->debug == DEBUG_ON && env->debug_lvl >= DEBUG_THIRD_LVL)
			ft_printf("ADV %d (%#.4x -> %#.4x)\n", ret, process->pc
					, process->pc + ret);
		increase_pc(process, ret);
	}
	process->queued_op = 0;
}

static void	setup_new_inst(t_env *env, t_process *process)
{
	int	opcode;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->cycles_left = 1;
	else
	{
		process->queued_op = opcode;
		process->cycles_left = g_op[opcode - 1].cycles;
	}
}

void		process_instructions(t_env *env)
{
	t_list		*cur;
	t_process	*process;

	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->cycles_left == 0)
			setup_new_inst(env, process);
		process->cycles_left -= 1;
		if (process->cycles_left == 0)
			exec_inst(env, process);
		cur = cur->next;
	}
}
