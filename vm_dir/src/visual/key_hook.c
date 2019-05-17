/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 06:22:11 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 02:21:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "visual.h"

t_data	g_data;

static int		wait_input(void)
{
	int	ch;

	while ((ch = getch()))
	{
		if (ch == 27)
			return (0);
		else if (ch == ' ')
		{
			mvwprintw(g_data.hud, 7 * TXT_HUD_PADD - 2, X_HUD_PADD
					, "**RUNNING**");
			wrefresh(g_data.hud);
			break ;
		}
	}
	return (1);
}

static void		time_manager(int ch)
{
	if (ch == 'r')
	{
		if (g_data.time - SPEED_INC <= MIN_SPEED)
			g_data.time = MIN_SPEED;
		else
			g_data.time -= SPEED_INC;
	}
	else if (ch == 'q')
	{
		if (g_data.time + SPEED_INC >= MAX_SPEED)
			g_data.time = MAX_SPEED;
		else
			g_data.time += SPEED_INC;
	}
}

int				key_hook(void)
{
	int	ch;

	ch = getch();
	if (ch == 'r' || ch == 'q')
		time_manager(ch);
	else if (ch == 27)
		return (0);
	else if (ch == ' ')
	{
		mvwprintw(g_data.hud, 7 * TXT_HUD_PADD - 2, X_HUD_PADD, "**PAUSED**");
		wrefresh(g_data.hud);
		if (!wait_input())
			return (0);
	}
	return (1);
}
