/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_levenshtein.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:00:43 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/05 10:47:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_min3(int a, int b, int c)
{
	if (a < b)
		return (ft_min(a, c));
	return (ft_min(b, c));
}

static void		ft_free_matrix(size_t **matrix, size_t size)
{
	size_t	index;

	index = 0;
	while (index <= size)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

static size_t	**ft_malloc_matrix(size_t s1_len, size_t s2_len)
{
	size_t	**matrix;
	size_t	idx;

	if (!(matrix = (size_t **)malloc((s2_len + 1) * sizeof(*matrix))))
		return (NULL);
	idx = 0;
	while (idx <= s2_len)
	{
		if (!(matrix[idx] = (size_t *)malloc((s1_len + 1) * sizeof(**matrix))))
		{
			ft_free_matrix(matrix, idx);
			return (NULL);
		}
		idx++;
	}
	return (matrix);
}

static int		ft_matrix_valfree(size_t **matrix, size_t s1_len, size_t s2_len)
{
	int	res;

	res = (int)matrix[s2_len][s1_len];
	ft_free_matrix(matrix, s2_len);
	return (res);
}

int				ft_levenshtein(const char *s1, const char *s2)
{
	size_t	x;
	size_t	y;
	size_t	len[2];
	size_t	**matrix;

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (!(matrix = ft_malloc_matrix(len[0], len[1])))
		return (-1);
	matrix[0][0] = 0;
	x = 0;
	while (++x <= len[1])
		matrix[x][0] = matrix[x - 1][0] + 1;
	y = 0;
	while (++y <= len[0])
		matrix[0][y] = matrix[0][y - 1] + 1;
	x = 0;
	while (++x <= len[1])
	{
		y = 0;
		while (++y <= len[0])
			matrix[x][y] = ft_min3(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1
					, matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));
	}
	return (ft_matrix_valfree(matrix, len[0], len[1]));
}
