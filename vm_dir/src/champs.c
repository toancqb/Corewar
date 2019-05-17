/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:15:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:20:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include "parsing.h"
#include "champion.h"
#include "process.h"
#include "visual.h"

t_error		create_champs(t_env *env, char **argv, int argc, int cur_arg)
{
	int		id;
	t_champ	champ;
	t_list	*node;
	int		total;

	ft_memset(&champ, 0, sizeof(t_champ));
	total = 0;
	while (cur_arg < argc)
	{
		if (total == MAX_PLAYERS)
			return (ERR_TOOMANYCHAMPS);
		else if (!set_champ_id(env, argv, &cur_arg, &id))
			return (ERR_WRONGNOPT);
		else if (argv[cur_arg] == NULL)
			return (ERR_NOCHAMPNAME);
		else if (!read_file(argv[cur_arg], &champ))
			return (ERR_CHAMPREAD);
		else if ((node = ft_lstnew(&champ, sizeof(t_champ))) == NULL)
			return (ERR_UNEXPECTED);
		g_data.champ[total++] = id;
		((t_champ *)node->content)->id = id;
		ft_lstpush(&env->champ_lst, node);
		cur_arg++;
	}
	return (ERR_NOERROR);
}

void		setup_champ(t_env *env, t_champ *champ, int pc)
{
	t_process	*process;

	ft_memcpy(&env->arena[pc], champ->prog, champ->header.prog_size);
	if (env->visu != VISU_ON)
		ft_printf("Champion \"%s\" (\"%s\") (%d bytes) has been loaded\n"
				, champ->header.prog_name
				, champ->header.comment
				, champ->header.prog_size);
	process = create_process(env, champ);
	if (process != NULL)
		process->pc = pc;
	else
	{
		if (env->visu != VISU_ON)
			ft_dprintf(2, "corewar: error: Unable to create process for \"%s\""
					, champ->header.prog_name);
	}
}

void		print_winner_champ(t_env *env)
{
	int		best_cycle;
	t_list	*best_champ;
	t_list	*cur_champ;

	best_cycle = -1;
	best_champ = NULL;
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (best_cycle <= ((t_champ *)cur_champ->content)->live_cycle)
		{
			best_cycle = ((t_champ *)cur_champ->content)->live_cycle;
			best_champ = cur_champ;
		}
		cur_champ = cur_champ->next;
	}
	if (best_champ != NULL)
	{
		if (env->visu == VISU_ON)
			print_winner_visu((t_champ *)best_champ->content);
		else
			ft_printf("Champion %d (\"%s\") has won!\n"
					, ((t_champ *)best_champ->content)->id
					, ((t_champ *)best_champ->content)->header.prog_name);
	}
}
