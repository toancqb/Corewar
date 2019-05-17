/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:38:06 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 05:35:29 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include "libft.h"
#include "asm.h"

t_error		create_cor(t_data *data, char *str)
{
	t_error err_id;
	int		fd;

	err_id = ERR_NOERROR;
	if (!(data->file_name = get_file_name(str)))
		return (ERR_MALLOC);
	if ((fd = open(data->file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644)) < 0)
		return (ERR_ERRNO);
	fill_header(data, fd);
	err_id = fill_instruction(data, fd);
	close(fd);
	return (err_id);
}
