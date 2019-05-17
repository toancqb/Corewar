/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 02:12:02 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 02:15:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "dasm.h"

t_error	get_header(t_data *data, int fd)
{
	int	ret;

	ret = read(fd, data->buf, HEADER_SIZE);
	if (ret < HEADER_SIZE)
		return (ERR_SIZEHEADER);
	data->buf[ret] = '\0';
	write_header(data, NAME_STR, 4, ft_strlen(data->buf + 4));
	swap_bytes(((uint8_t*)data->buf + 136), 4);
	data->prog_size = *((uint32_t*)(data->buf + 136));
	write_header(data, COMMENT_STR, 140, ft_strlen(data->buf + 140));
	write(data->fd, "\n", 1);
	return (ERR_NOERROR);
}

int		get_name(t_data *data, char *filepath)
{
	char	*str;
	int		idx;
	int		len;

	if (filepath != NULL)
	{
		len = ft_strlen(filepath) - 1;
		idx = len;
		while (idx >= 0)
		{
			if (filepath[idx] == '/')
				break ;
			idx -= 1;
		}
		if (rename_file(&filepath[idx + 1]) == 0)
			return (0);
		str = (idx == -1) ? ft_strdup(filepath) : ft_strdup(&filepath[idx + 1]);
		if (str == NULL)
			return (0);
		data->filename = str;
		return (1);
	}
	return (0);
}

int		rename_file(char *filename)
{
	int	len;
	int	idx;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	idx = len - 4;
	if (ft_strequ(&filename[idx], ".cor") == 0)
		return (0);
	ft_bzero(&filename[idx + 1], 3);
	filename[idx + 1] = 's';
	return (1);
}

int		open_file(t_data *data, char *filepath)
{
	int	fd;

	if (access(filepath, F_OK) != 0)
		return (-1);
	if ((fd = open(filepath, O_RDONLY)) == -1)
		return (-1);
	if (get_name(data, filepath) == 0)
		return (-1);
	return (fd);
}

int		create_newfile(t_data *data)
{
	data->fd = open(data->filename, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (data->fd == -1)
		return (ERR_ERRNO);
	return (ERR_NOERROR);
}
