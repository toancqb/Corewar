/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 06:17:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "corewar.h"
#include "options.h"

static t_error	parse_dump_opt(t_env *env, const char *optarg)
{
	long	dump_cycles;
	char	*endptr;

	if (optarg == NULL)
		return (ERR_WRONGDUMPOPT);
	else if (env->visu == VISU_ON)
		return (ERR_OPTCONFLICT);
	dump_cycles = ft_strtol(optarg, &endptr, 10);
	if (*endptr != '\0' || dump_cycles < 0 || dump_cycles > INT_MAX)
		return (ERR_WRONGDUMPOPT);
	env->dump_cycles = (int)dump_cycles;
	return (ERR_NOERROR);
}

static t_error	parse_debug_opt(t_env *env, const char *optarg)
{
	long	value;
	char	*endptr;

	if (env->visu == VISU_ON)
		return (ERR_OPTCONFLICT);
	else if (optarg == NULL)
		return (ERR_WRONGDEBUGOPT);
	value = ft_strtol(optarg, &endptr, 10);
	if (value != DEBUG_FIRST_LVL
			&& value != DEBUG_SECOND_LVL
			&& value != DEBUG_THIRD_LVL)
		return (ERR_WRONGDEBUGOPT);
	env->debug_lvl = value;
	env->debug = DEBUG_ON;
	return (ERR_NOERROR);
}

static t_error	parse_visual_opt(t_env *env, const char *optarg)
{
	(void)optarg;
	if (env->debug == DEBUG_ON || env->dump_cycles != -1)
		return (ERR_OPTCONFLICT);
	env->visu = VISU_ON;
	return (ERR_NOERROR);
}

t_error			parse_opts(t_env *env, char **argv, int *cur_arg)
{
	static t_opt	opts[] = {
		{"--dump", parse_dump_opt, OPT_MUSTHAVEARG},
		{"--debug", parse_debug_opt, OPT_MUSTHAVEARG},
		{"-v", parse_visual_opt, OPT_NOARG},
		{NULL, NULL, 0}
	};
	t_error			err_id;

	*cur_arg = 1;
	while (argv[*cur_arg] != NULL && argv[*cur_arg][0] == '-')
	{
		if (ft_strequ("-n", argv[*cur_arg]))
			break ;
		else if (ft_strequ("--", argv[*cur_arg]))
		{
			*cur_arg += 1;
			break ;
		}
		err_id = parse_opt(env, opts, argv, cur_arg);
		if (err_id != ERR_NOERROR)
			return (err_id);
		*cur_arg += 1;
	}
	return (ERR_NOERROR);
}
