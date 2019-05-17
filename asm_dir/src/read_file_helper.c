/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:16:04 by qtran             #+#    #+#             */
/*   Updated: 2019/02/21 05:03:33 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "asm.h"

t_error	check_first_line(int fd)
{
	char	buf[1];
	int		ret;

	if ((ret = read(fd, buf, 1)) < 1)
		return ((ret == -1) ? ERR_ERRNO : ERR_BADFMT);
	if (buf[0] != '\n' && buf[0] != '\t' && buf[0] != '#' && buf[0] != '.'
			&& buf[0] != ';' && buf[0] != ' ')
		return (ERR_HEADER);
	if ((ret = lseek(fd, 0, SEEK_SET)) == -1)
		return (ERR_ERRNO);
	return (ERR_NOERROR);
}

char	*skip_tab_n_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

t_error	skip_useless(int fd, char **line)
{
	char	*str;
	int		ret;

	while ((ret = get_next_line(fd, line)) > 0)
	{
		if (((str = skip_tab_n_space(*line)) != NULL)
				&& (str[0] != '#' && str[0] != '\0' && str[0] != ';'))
			break ;
		ft_strdel(line);
	}
	if (ret <= 0)
		return (ERR_HEADER);
	return (ERR_NOERROR);
}

char	*get_dquote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] == '\0' && str[i] != '"')
		return (NULL);
	return (&str[i + 1]);
}

t_error	check_endline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] != '#' && str[i] != '\0' && str[i] != ';')
		return (ERR_HEADER);
	return (ERR_NOERROR);
}
