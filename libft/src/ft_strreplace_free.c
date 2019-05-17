/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:23:05 by gguichar          #+#    #+#             */
/*   Updated: 2018/09/04 21:07:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strreplace_free(char *s, const char *from, const char *to)
{
	char	*str;

	str = ft_strreplace(s, from, to);
	free(s);
	return (str);
}
