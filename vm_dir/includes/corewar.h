/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:04:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <inttypes.h>
# include "libft.h"
# include "op.h"
# include "champion.h"
# include "process.h"

# define DEBUG_ON			1
# define DEBUG_FIRST_LVL	1
# define DEBUG_SECOND_LVL	2
# define DEBUG_THIRD_LVL	3
# define VISU_ON			1

enum			e_error
{
	ERR_NOERROR = 0,
	ERR_UNEXPECTED = 1,
	ERR_NOCHAMPNAME,
	ERR_OPTCONFLICT,
	ERR_WRONGOPT,
	ERR_WRONGNOPT,
	ERR_WRONGDEBUGOPT,
	ERR_WRONGDUMPOPT,
	ERR_CHAMPREAD,
	ERR_NOCHAMPS,
	ERR_TOOMANYCHAMPS
};

typedef struct s_env	t_env;
typedef enum e_error	t_error;

struct			s_env
{
	t_list		*champ_lst;
	t_list		*process_lst;
	uint8_t		arena[MEM_SIZE];
	int			debug;
	int			debug_lvl;
	int			visu;
	int			cur_cycle;
	int			dump_cycles;
	int			cycle_to_die;
	int			cycle_before_die;
	int			cycle_checks_no_decr;
};

typedef struct	s_op
{
	int			(*fn)(t_env *, t_process *, uint8_t *);
	int			cycles;
}				t_op;

int				set_champ_id(t_env *env, char **argv, int *cur_arg, int *id);
t_error			create_champs(t_env *env, char **argv, int argc, int cur_arg);
void			setup_champ(t_env *env, t_champ *champ, int pc);
void			print_winner_champ(t_env *env);

t_process		*create_process(t_env *env, t_champ *champ);

void			fix_pc_offset(int *offset);
void			increase_pc(t_process *process, int value);

void			process_instructions(t_env *env);
void			run_cycles_loop(t_env *env);

const char		*str_to_error(t_error err_id);
void			print_arena(t_env *env);

#endif
