/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 23:00:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/10 23:02:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			elem = *alst;
			while (elem->next != NULL)
				elem = elem->next;
			elem->next = new;
		}
	}
}
