/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:48:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/20 04:50:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fix_pc_offset(int *offset)
{
	while (*offset < 0)
		*offset += MEM_SIZE;
	if (*offset >= MEM_SIZE)
		*offset %= MEM_SIZE;
}

void	increase_pc(t_process *process, int value)
{
	process->pc += value;
	fix_pc_offset(&process->pc);
}
