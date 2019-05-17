/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:32:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/21 06:46:00 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMPION_H
# define CHAMPION_H

# include "op.h"

typedef struct	s_champ
{
	t_header		header;
	unsigned char	prog[CHAMP_MAX_SIZE];
	int				live_cycle;
	int				lives;
	int				id;
}				t_champ;

#endif
