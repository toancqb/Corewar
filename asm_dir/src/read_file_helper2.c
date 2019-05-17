/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:21:48 by qtran             #+#    #+#             */
/*   Updated: 2019/02/21 06:32:09 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "asm.h"

t_error	fill_prog_name(t_data *data, int fd, char **str, char **line)
{
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (ft_strlen(*str) + 1 + ft_strlen(data->header.prog_name)
			> PROG_NAME_LENGTH)
		err_id = ERR_HEADER;
	if (err_id == ERR_NOERROR)
	{
		ft_strcat(data->header.prog_name, *str);
		ft_strcat(data->header.prog_name, "\n");
		ft_strdel(line);
		if (get_next_line(fd, line) <= 0)
			err_id = ERR_HEADER;
		*str = *line;
	}
	return (err_id);
}

t_error	get_name(t_data *data, int fd, char **line)
{
	t_error	err_id;
	char	*ndl;
	char	*s;

	s = NULL;
	ndl = NULL;
	err_id = ERR_NOERROR;
	if (*line != NULL && (s = skip_tab_n_space(*line)) == NULL)
		return (ERR_HEADER);
	if ((ft_strnequ(s, ".name", 5) == 0) || ((s = get_dquote(s + 5)) == NULL))
		err_id = ERR_HEADER;
	while (err_id == ERR_NOERROR && (ndl = ft_strchr(s, '"')) == NULL)
		err_id = fill_prog_name(data, fd, &s, line);
	s = (s == NULL) ? *line : s;
	if (err_id == ERR_NOERROR && (ft_strlen(data->header.prog_name)
				+ (ndl - s) > PROG_NAME_LENGTH))
		err_id = ERR_HEADER;
	else if (ft_strlen(data->header.prog_name) + (ndl - s) <= PROG_NAME_LENGTH)
		ft_strncat(data->header.prog_name, s, ndl - s);
	else
		err_id = ERR_HEADER;
	if (err_id == ERR_NOERROR && ndl != NULL)
		err_id = check_endline(ndl + 1);
	ft_strdel(line);
	return (err_id);
}

t_error	fill_comment(t_data *data, int fd, char **str, char **line)
{
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (ft_strlen(*str) + 1 + ft_strlen(data->header.comment)
			> COMMENT_LENGTH)
		err_id = ERR_HEADER;
	if (err_id == ERR_NOERROR)
	{
		ft_strcat(data->header.comment, *str);
		ft_strcat(data->header.comment, "\n");
		ft_strdel(line);
		if (get_next_line(fd, line) <= 0)
			err_id = ERR_HEADER;
		*str = *line;
	}
	return (err_id);
}

t_error	get_comment(t_data *data, int fd, char **line)
{
	t_error	err_id;
	char	*needle;
	char	*s;

	s = NULL;
	needle = NULL;
	err_id = ERR_NOERROR;
	if (*line != NULL && (s = skip_tab_n_space(*line)) == NULL)
		return (ERR_HEADER);
	if ((ft_strnequ(s, ".comment", 8) == 0) || (s = get_dquote(s + 8)) == NULL)
		err_id = ERR_HEADER;
	while (err_id == ERR_NOERROR && (needle = ft_strchr(s, '"')) == NULL)
		err_id = fill_comment(data, fd, &s, line);
	s = (s == NULL) ? *line : s;
	if (err_id == ERR_NOERROR && (ft_strlen(data->header.comment)
				+ (needle - s) > COMMENT_LENGTH))
		err_id = ERR_HEADER;
	else if (ft_strlen(data->header.comment) + (needle - s) <= COMMENT_LENGTH)
		ft_strncat(data->header.comment, s, needle - s);
	else
		err_id = ERR_HEADER;
	if (err_id == ERR_NOERROR && needle != NULL)
		err_id = check_endline(needle + 1);
	ft_strdel(line);
	return (err_id);
}
