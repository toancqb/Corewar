/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:03:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/21 06:45:51 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <inttypes.h>
# include "op.h"

# define MAX_INST_SIZE 32

typedef struct s_process	t_process;

struct	s_process
{
	int			champ_id;
	uint32_t	reg[REG_NUMBER];
	int			pc;
	int			carry;
	int			queued_op;
	int			cycles_left;
	int			lives;
	int			last_live;
};

#endif
