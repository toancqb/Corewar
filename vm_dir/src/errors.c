/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:44:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/23 05:05:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const char	*str_to_error(t_error err_id)
{
	static char	buffer[256];

	if (err_id == ERR_UNEXPECTED)
		ft_strcpy(buffer, "Unexpected error");
	else if (err_id == ERR_NOCHAMPNAME)
		ft_strcpy(buffer, "No champion name after champ number");
	else if (err_id == ERR_WRONGNOPT)
		ft_strcpy(buffer, "Wrong champion number option");
	else if (err_id == ERR_WRONGDUMPOPT)
		ft_strcpy(buffer, "Dump option number should be a positive integer");
	else if (err_id == ERR_WRONGDEBUGOPT)
		ft_strcpy(buffer, "Wrong debug level");
	else if (err_id == ERR_NOCHAMPS)
		ft_strcpy(buffer, "You must specify at least one champion");
	else if (err_id == ERR_TOOMANYCHAMPS)
		ft_strcpy(buffer, "There is too many champions");
	else if (err_id == ERR_OPTCONFLICT)
	{
		ft_strcpy(buffer, "Please check your options carefully ");
		ft_strcat(buffer, "it seems that there is a conflict in it");
	}
	return (buffer);
}
