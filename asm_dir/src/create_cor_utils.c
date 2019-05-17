/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 04:41:40 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 05:36:14 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "op.h"
#include "libft.h"
#include "asm.h"

t_filter	*is_label(char *str, t_list *head)
{
	t_filter	*label;
	t_list		*node;
	int			offset;

	node = head;
	if (ft_strnequ("%:", str, 2) == 0 && *str != ':')
		return (NULL);
	offset = 1 + (*str == '%');
	while (node != NULL)
	{
		label = (t_filter*)node->content;
		if (ft_strlen(label->op.name) - 1 == ft_strlen(str + offset)
				&& ft_strnequ(label->op.name, str + offset,
					ft_strlen(str + offset)))
			return (label);
		node = node->next;
	}
	return (NULL);
}

char		*get_file_name(char *str)
{
	char	*file_name;
	size_t	len;

	len = ft_strlen(str);
	while (len != 0 && str[len] != '.')
		len--;
	if (len == 0)
		len = ft_strlen(str);
	if (!(file_name = ft_strnew(len + 5)))
		return (NULL);
	ft_memcpy(file_name, str, len);
	ft_strcat(file_name, ".cor");
	return (file_name);
}

void		fill_header(t_data *data, int fd)
{
	t_header *header;

	header = &data->header;
	header->magic = COREWAR_EXEC_MAGIC;
	swap_bytes((unsigned char *)&header->magic, 4);
	write(fd, "\0", 1);
	write_magic((unsigned char *)&header->magic, fd, 4);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	swap_bytes((unsigned char *)&data->header.prog_size, 4);
	write(fd, &data->header.prog_size, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
}

t_error		fill_instruction(t_data *data, int fd)
{
	t_filter	*elem;
	int			offset;
	int			idx;

	idx = 0;
	while (idx < data->f_size)
	{
		elem = &data->filter[idx];
		if ((offset = manage_filter(elem, data, fd)) == 0)
			return (ERR_ARGNB);
		idx += offset;
	}
	return (ERR_NOERROR);
}
