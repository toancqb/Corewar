/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:44:54 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/29 17:09:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*offset;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	if (new == NULL)
		return (NULL);
	offset = new;
	while (lst->next != NULL)
	{
		lst = lst->next;
		offset->next = f(lst);
		if (offset->next != NULL)
			offset = offset->next;
	}
	return (new);
}
