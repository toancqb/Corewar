/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 00:05:44 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/23 00:41:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include "visual.h"

t_data		g_data;

static void	end_ncurses(int sig)
{
	delwin(g_data.hud);
	endwin();
	ft_lstfree(&g_data.env->champ_lst);
	ft_lstfree(&g_data.env->process_lst);
	exit(sig);
}

void		sig_handler(void)
{
	signal(SIGABRT, end_ncurses);
	signal(SIGFPE, end_ncurses);
	signal(SIGILL, end_ncurses);
	signal(SIGINT, end_ncurses);
	signal(SIGSEGV, end_ncurses);
	signal(SIGTERM, end_ncurses);
}
