/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:56:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 23:26:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "visual.h"
#include "op.h"

static t_list	*free_old_process(t_env *env, t_list *prev, t_list *cur
		, t_process *process)
{
	t_list	*next;

	next = cur->next;
	if (prev == NULL)
		env->process_lst = next;
	else
		prev->next = next;
	if (env->debug == DEBUG_ON && env->debug_lvl >= DEBUG_THIRD_LVL)
		ft_printf("Process hasn't lived for %d cycles\n"
				, env->cur_cycle - process->last_live);
	free(cur->content);
	free(cur);
	return (next);
}

static int		kill_old_process(t_env *env)
{
	int			lives;
	t_list		*prev;
	t_list		*cur;
	t_process	*process;

	lives = 0;
	prev = NULL;
	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->lives == 0)
			cur = free_old_process(env, prev, cur, process);
		else
		{
			lives += process->lives;
			process->lives = 0;
			prev = cur;
			cur = cur->next;
		}
	}
	return (lives);
}

static int		decrease_cycle_to_die(t_env *env)
{
	if (kill_old_process(env) >= NBR_LIVE)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		env->cycle_checks_no_decr = 0;
		return (1);
	}
	else
	{
		env->cycle_checks_no_decr++;
		if (env->cycle_checks_no_decr == MAX_CHECKS)
		{
			env->cycle_to_die -= CYCLE_DELTA;
			env->cycle_checks_no_decr = 0;
			return (1);
		}
	}
	return (0);
}

static int		visual_manage_cycle(t_env *env)
{
	print_lifebar_visu(env->champ_lst);
	refresh_champ_lives(env);
	return (key_hook());
}

void			run_cycles_loop(t_env *env)
{
	while (env->process_lst != NULL)
	{
		if (env->debug == DEBUG_ON)
			ft_printf("It is now cycle %d\n", env->cur_cycle);
		process_instructions(env);
		if (env->cur_cycle == env->dump_cycles)
		{
			print_arena(env);
			break ;
		}
		if (env->cycle_before_die > 0)
			env->cycle_before_die -= 1;
		if (env->cycle_before_die <= 0)
		{
			if (decrease_cycle_to_die(env) && env->debug == DEBUG_ON)
				ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
			env->cycle_before_die = env->cycle_to_die;
		}
		if (env->visu == VISU_ON && !visual_manage_cycle(env))
			break ;
		env->cur_cycle += 1;
	}
}
