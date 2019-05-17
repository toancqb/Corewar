/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 04:07:07 by wta               #+#    #+#             */
/*   Updated: 2019/02/21 05:21:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"

t_error	lst_lab_check(t_list_ref *list, t_list *node)
{
	t_list *tmp;

	tmp = NULL;
	if (list->head != NULL)
	{
		tmp = list->head;
		while (tmp != NULL)
		{
			if (ft_strequ(((t_op*)node->content)->name,
						((t_op*)tmp->content)->name) == 1)
			{
				free(node);
				return (ERR_DUPLABEL);
			}
			tmp = tmp->next;
		}
	}
	lst_pushback(list, node);
	return (ERR_NOERROR);
}

void	lst_pushback(t_list_ref *list, t_list *node)
{
	if (list != NULL && node != NULL)
	{
		if (list->head == NULL)
		{
			list->head = node;
			list->tail = node;
		}
		else
		{
			list->tail->next = node;
			list->tail = node;
		}
	}
}

t_list	*lstnew_mallocfree(void *content)
{
	t_list	*elem;

	if ((elem = (void*)malloc(sizeof(t_list))) != NULL)
	{
		elem->next = NULL;
		elem->content = content;
		elem->content_size = sizeof(content);
	}
	return (elem);
}

void	lst_free(t_list_ref *list)
{
	t_list	*ref;

	ref = list->head;
	while (ref != NULL)
	{
		ref = ref->next;
		free(list->head);
		list->head = ref;
	}
}
