/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 03:11:42 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 00:40:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void	init_screen(t_env *env)
{
	struct winsize	win;

	g_data.env = env;
	g_data.cursor = (t_int2){X_PADD, Y_PADD};
	initscr();
	start_color();
	use_default_colors();
	ioctl(0, TIOCGSIZE, &win);
	curs_set(0);
	sig_handler();
	g_data.hud = subwin(stdscr, win.ws_row - 2,
			win.ws_col - HUD_COL, 1, HUD_COL - 2);
	wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwaddstr(stdscr, 0, (win.ws_col * 0.5) - 9, " COREWAR ");
	wborder(g_data.hud, '|', '|', '-', '-', '+', '+', '+', '+');
	nodelay(stdscr, TRUE);
	noecho();
	g_data.win = stdscr;
	g_data.time = SPEED;
	print_init_state(env);
	print_champ(env);
	print_init_hud(env);
}

void	init_champ_color(void)
{
	init_pair(0, -1, -1);
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_BLUE, -1);
	init_pair(3, COLOR_GREEN, -1);
	init_pair(4, COLOR_YELLOW, -1);
	init_pair(5, -1, COLOR_RED);
	init_pair(6, -1, COLOR_BLUE);
	init_pair(7, -1, COLOR_GREEN);
	init_pair(8, -1, COLOR_YELLOW);
}

void	print_init_state(t_env *env)
{
	t_int2	cursor;
	t_int2	pos;

	(void)env;
	init_champ_color();
	cursor = (t_int2) {X_PADD, Y_PADD};
	pos = (t_int2) {0, 0};
	while (pos.y < HEIGHT)
	{
		cursor.x = X_PADD;
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			mvwprintw(g_data.win, cursor.y, cursor.x, "00 ");
			cursor.x += 3;
			pos.x += 1;
		}
		cursor.y += 1;
		pos.y += 1;
	}
}
