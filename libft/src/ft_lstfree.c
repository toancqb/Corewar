/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:29:36 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 17:15:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_elem(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void		*ft_lstfree(t_list **alst)
{
	return (ft_lstdel(alst, &free_elem));
}
