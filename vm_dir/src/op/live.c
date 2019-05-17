/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 05:20:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "champion.h"
#include "func_op.h"
#include "op.h"

static void	live_champ(t_env *env, t_champ *champ)
{
	champ->live_cycle = env->cur_cycle;
	champ->lives += 1;
	if (env->visu != VISU_ON)
		ft_printf("Champion %d (\"%s\") is alive\n", champ->id
				, champ->header.prog_name);
}

static void	debug_mode(int param, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "live");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: %d\n", "live", param);
}

int			live(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*champ;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, REG_DIR) + 1;
	champ = env->champ_lst;
	while (champ != NULL)
	{
		if (((t_champ *)champ->content)->id == (int)decode.tab[0].value)
		{
			live_champ(env, (t_champ *)champ->content);
			break ;
		}
		champ = champ->next;
	}
	cur_process->lives += 1;
	cur_process->last_live = env->cur_cycle;
	if (env->debug == DEBUG_ON)
		debug_mode((int)decode.tab[0].value, env->debug_lvl);
	return (ret);
}
