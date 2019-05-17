/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 06:11:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H

# include <inttypes.h>
# include "corewar.h"
# include "process.h"
# include "op.h"

# define BAD_REG	0
# define SHORT_DIR	2
# define REG_DIR	4

typedef struct	s_arg
{
	int			type;
	uint32_t	value;
}				t_arg;

typedef struct	s_decode
{
	t_env		*env;
	int			max_args;
	t_process	*process;
	t_arg		tab[MAX_ARGS_NUMBER];
}				t_decode;

/*
** FONCTIONS VMs.
*/

int				live(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ld(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				st(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				add(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				sub(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ft_and(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ft_or(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ft_xor(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				zjmp(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ldi(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				sti(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ft_fork(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				lld(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				lldi(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				ft_lfork(t_env *env, t_process *cur_process
		, uint8_t *bytes);
int				aff(t_env *env, t_process *cur_process
		, uint8_t *bytes);

/*
**	UTILS
*/

void			swap_bytes(uint8_t *str, int size);
void			fill_buff_from_arena(t_env *env, uint8_t *buffer, size_t size
		, int offset);
void			write_in_arena(t_env *env, uint8_t *bytes, size_t size
		, int offset);
int				decode_args(t_decode *decode, uint8_t *args
		, uint8_t encoding_byte, int dir_size);
void			fill_decode(t_env *env, t_process *process, t_decode *decode
		, int value);
void			store_multitype(uint32_t *buffer, t_decode decode, t_arg arg
		, int is_long);

#endif
