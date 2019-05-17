/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:01:13 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 00:40:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar.h"

# define HUD_COL		250
# define WIDTH			64
# define HEIGHT			64
# define X_PADD			27
# define Y_PADD			9
# define X_HUD_PADD		4
# define Y_HUD_PADD		2
# define TXT_HUD_PADD	5
# define SPEED			50000
# define MAX_SPEED		1000000
# define MIN_SPEED		500
# define SPEED_INC		3000

typedef struct	s_int2
{
	int			x;
	int			y;
}				t_int2;

typedef struct	s_data
{
	t_env		*env;
	WINDOW		*win;
	WINDOW		*hud;
	int			champ[MAX_PLAYERS];
	int			time;
	t_int2		cursor;
}				t_data;

extern t_data	g_data;

void			init_screen(t_env *env);
void			print_init_hud(t_env *env);
void			print_init_state(t_env *env);
void			print_champ(t_env *env);
void			init_champ_color(void);
void			print_bottom(void);

void			write_ncurses(uint8_t *bytes_ptr, int id, int size, int index);
void			refresh_champ_lives(t_env *env);
void			print_winner_visu(t_champ *winner);
void			print_lifebar_visu(t_list *champ_lst);

int				champ_color(int id);
int				key_hook(void);
void			sig_handler(void);
double			ft_round(double value);
void			loop_screen(void);

#endif
