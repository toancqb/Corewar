/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 02:08:24 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 02:54:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "dasm.h"

void	write_header(t_data *data, char *str, int idx, int len)
{
	char	*name;

	write(data->fd, str, ft_strlen(str));
	write(data->fd, "\"", 1);
	name = data->buf + idx;
	write(data->fd, name, len);
	write(data->fd, "\"\n", 2);
}
