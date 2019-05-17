/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 05:02:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:06:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "corewar.h"
#include "champion.h"

static int	get_next_champid(t_env *env)
{
	int		id;
	t_list	*cur_champ;

	id = -1;
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (id == ((t_champ *)cur_champ->content)->id)
		{
			id--;
			cur_champ = env->champ_lst;
			continue ;
		}
		cur_champ = cur_champ->next;
	}
	return (id);
}

static int	is_duplicated_champid(t_env *env, int id)
{
	t_list	*cur_champ;

	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (id == ((t_champ *)cur_champ->content)->id)
			return (1);
		cur_champ = cur_champ->next;
	}
	return (0);
}

int			set_champ_id(t_env *env, char **argv, int *cur_arg, int *id)
{
	long	parsed_id;
	char	*endptr;

	if (!ft_strequ("-n", argv[*cur_arg]))
		*id = get_next_champid(env);
	else
	{
		*cur_arg += 1;
		if (argv[*cur_arg] == NULL)
			return (0);
		parsed_id = ft_strtol(argv[*cur_arg], &endptr, 10);
		if (*endptr != '\0' || parsed_id < INT_MIN || parsed_id > INT_MAX)
			return (0);
		*id = parsed_id;
		if (is_duplicated_champid(env, *id))
			return (0);
		*cur_arg += 1;
	}
	return (1);
}
