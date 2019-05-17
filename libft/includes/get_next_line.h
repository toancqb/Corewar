/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 20:09:16 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/30 02:14:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# define BUFF_SIZE 4096

typedef struct	s_fd
{
	int			fd;
	char		*data;
	char		*offset;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(const int fd, char **line);

#endif
