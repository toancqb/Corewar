/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 08:22:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 08:25:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

double	ft_round(double value)
{
	if (value - (int)value < 0.5)
		return ((int)value);
	else
		return ((int)value + 1);
}
