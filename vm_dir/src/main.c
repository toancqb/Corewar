/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:53:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include "champion.h"
#include "parsing.h"
#include "visual.h"
#include "options.h"

static void	show_help(t_error err_id, char **argv, int cur_arg)
{
	if (err_id == ERR_WRONGOPT)
		ft_dprintf(2, "corewar: error: Invalid option %s\n", argv[cur_arg]);
	else if (err_id != ERR_CHAMPREAD)
		ft_dprintf(2, "corewar: error: %s\n", str_to_error(err_id));
	ft_printf("USAGE: %s [options] <champions>\n", argv[0]);
	ft_printf("You can load at most %d champions\n\n", MAX_PLAYERS);
	ft_printf("OPTIONS:\n");
	ft_printf("  --dump <cycle>\tDumps memory at specified cycle then "
			"exits\n");
	ft_printf("  --debug <level>\tEnable debug mode (levels: 1, 2 or 3)\n");
	ft_printf("  -n [id] <champion>\tUse custom id for champion\n");
	ft_printf("  -v\t\t\tEnable visual mode\n");
}

static void	run_vm(t_env *env)
{
	size_t	idx;
	size_t	nb_champs;
	t_list	*cur_champ;

	if (env->visu == VISU_ON)
		init_screen(env);
	idx = 0;
	nb_champs = ft_lstsize(env->champ_lst);
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		setup_champ(env, (t_champ *)cur_champ->content
				, (MEM_SIZE / nb_champs) * idx);
		cur_champ = cur_champ->next;
		idx++;
	}
	if (env->dump_cycles == 0)
		print_arena(env);
	else
		run_cycles_loop(env);
	if (env->dump_cycles == -1
			|| env->dump_cycles > env->cur_cycle)
		print_winner_champ(env);
	if (env->visu == VISU_ON)
		loop_screen();
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		cur_arg;
	t_error	err_id;

	ft_memset(&env, 0, sizeof(t_env));
	env.cur_cycle = 1;
	env.cycle_to_die = CYCLE_TO_DIE;
	env.cycle_before_die = env.cycle_to_die;
	env.dump_cycles = -1;
	err_id = parse_opts(&env, argv, &cur_arg);
	if (err_id == ERR_NOERROR)
		err_id = create_champs(&env, argv, argc, cur_arg);
	if (err_id == ERR_NOERROR && env.champ_lst == NULL)
		err_id = ERR_NOCHAMPS;
	if (err_id == ERR_NOERROR)
		run_vm(&env);
	else
		show_help(err_id, argv, cur_arg);
	ft_lstfree(&env.champ_lst);
	ft_lstfree(&env.process_lst);
	return (err_id == ERR_NOERROR ? 0 : 1);
}
