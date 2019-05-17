/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 06:37:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 06:39:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "options.h"

static char	*get_optarg(const char *opt, char **argv, int *cur_arg)
{
	size_t	len;

	len = ft_strlen(opt);
	if (argv[*cur_arg][len] != '\0')
		return (argv[*cur_arg] + len);
	*cur_arg += 1;
	return (argv[*cur_arg]);
}

t_error		parse_opt(t_env *env, t_opt *opts, char **argv, int *cur_arg)
{
	const char	*opt;
	int			idx;
	const char	*optarg;

	opt = argv[*cur_arg];
	idx = 0;
	while (opts[idx].name != NULL)
	{
		if (ft_strstr(opt, opts[idx].name) == opt)
		{
			optarg = NULL;
			if (opts[idx].optarg_type == OPT_MUSTHAVEARG)
				optarg = get_optarg(opts[idx].name, argv, cur_arg);
			else if (opt[ft_strlen(opts[idx].name)] != '\0')
				return (ERR_WRONGOPT);
			return (opts[idx].fn(env, optarg));
		}
		idx++;
	}
	return (ERR_WRONGOPT);
}
