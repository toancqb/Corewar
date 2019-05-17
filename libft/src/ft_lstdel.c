/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 10:27:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*elem;
	t_list	*next;

	if (alst != NULL)
	{
		elem = *alst;
		while (elem != NULL)
		{
			next = elem->next;
			if (del != NULL)
				del(elem->content, elem->content_size);
			free(elem);
			elem = next;
		}
		*alst = NULL;
	}
	return (NULL);
}
