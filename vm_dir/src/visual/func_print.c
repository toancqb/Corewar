/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 03:14:43 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 11:16:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void		loop_screen(void)
{
	int	ch;

	nodelay(g_data.win, FALSE);
	while ((ch = getch()))
	{
		if (ch == 27)
		{
			delwin(g_data.hud);
			endwin();
			break ;
		}
	}
}

int			champ_color(int id)
{
	int	idx;

	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		if (id == g_data.champ[idx])
			return (idx + 1);
		idx++;
	}
	return (0);
}

static void	print_curs(t_int2 pos, uint8_t *bytes_ptr, int color, int idx)
{
	attron(COLOR_PAIR(color + 4));
	mvwprintw(g_data.win, pos.y + Y_PADD, pos.x * 3 + X_PADD, "%.2x"
			, bytes_ptr[idx]);
	attron(COLOR_PAIR(color));
	wrefresh(g_data.win);
	usleep(g_data.time);
}

void		write_ncurses(uint8_t *bytes_ptr, int id, int size, int index)
{
	t_int2	pos;
	int		idx;
	int		color;

	idx = size;
	init_champ_color();
	color = champ_color(id);
	fix_pc_offset(&index);
	pos = (t_int2) {index % WIDTH, index / HEIGHT};
	attron(COLOR_PAIR(color));
	while (--idx >= 0)
	{
		if (idx == (size - 1))
			print_curs(pos, bytes_ptr, color, idx);
		mvwprintw(g_data.win, pos.y + Y_PADD, pos.x * 3 + X_PADD, "%.2x"
				, bytes_ptr[idx]);
		index += 1;
		fix_pc_offset(&index);
		pos = (t_int2) {index % WIDTH, index / HEIGHT};
		mvwprintw(g_data.hud, 8 * TXT_HUD_PADD - 2, X_HUD_PADD, "Speed : %d"
				, MAX_SPEED - g_data.time);
		usleep(g_data.time);
		wrefresh(g_data.win);
	}
	attroff(COLOR_PAIR(color));
}

void		print_bottom(void)
{
	t_int2	dim;

	getmaxyx(g_data.hud, dim.y, dim.x);
	mvwprintw(g_data.hud, dim.y - 8, X_HUD_PADD
			, "   ___");
	mvwprintw(g_data.hud, dim.y - 7, X_HUD_PADD
			, "  / __\\___  _ __ _____      ____ _ _ __ ");
	mvwprintw(g_data.hud, dim.y - 6, X_HUD_PADD
			, " / /  / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|");
	mvwprintw(g_data.hud, dim.y - 5, X_HUD_PADD
			, "/ /__| (_) | | |  __/\\ V  V / (_| | |");
	mvwprintw(g_data.hud, dim.y - 4, X_HUD_PADD
			, "\\____/\\___/|_|  \\___| \\_/\\_/ \\__,_|_|");
	mvwprintw(g_data.hud, dim.y - 7, dim.x - 12, "gguichar");
	mvwprintw(g_data.hud, dim.y - 6, dim.x - 12, "rvalenti");
	mvwprintw(g_data.hud, dim.y - 5, dim.x - 12, "vifonne");
	mvwprintw(g_data.hud, dim.y - 4, dim.x - 12, "wta");
}
