/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 04:27:54 by wta               #+#    #+#             */
/*   Updated: 2019/02/18 04:31:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "asm.h"

int		replace_mod(char *str, char *new)
{
	int	idx;

	idx = 0;
	while (LABEL_CHARS[idx] != '\0')
	{
		if (str[-1] == LABEL_CHARS[idx])
		{
			new[0] = ' ';
			new[1] = '%';
			return (1);
		}
		idx += 1;
	}
	new[0] = str[0];
	return (0);
}

int		replace_colon(char *str, char *new)
{
	int	idx;

	idx = 0;
	while (LABEL_CHARS[idx] != '\0')
	{
		if (str[-1] == LABEL_CHARS[idx])
		{
			new[0] = ':';
			new[1] = ' ';
			return (1);
		}
		idx += 1;
	}
	new[0] = str[0];
	return (0);
}

void	expand_space(char *str, char *new, int len)
{
	int		idx;
	int		jdx;

	idx = 0;
	jdx = 0;
	while (jdx < len)
	{
		if (idx > 0 && str[idx] == '%')
			jdx += replace_mod(&str[idx], &new[jdx]);
		else if (idx > 0 && str[idx] == ':')
			jdx += replace_colon(&str[idx], &new[jdx]);
		else
			new[jdx] = str[idx];
		idx += 1;
		jdx += 1;
	}
}

char	*expand_label(char *str)
{
	char	*new;
	int		len;

	if ((len = cnt_space_to_add(str)) == -1)
		return (NULL);
	else if (len == 0)
		return (str);
	len += ft_strlen(str);
	if ((new = ft_strnew(len)) == NULL)
		return (NULL);
	expand_space(str, new, len);
	free(str);
	return (new);
}

char	*strjoin_add_c(char const *s1, char const *s2, char c)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = (s1 == NULL) ? 0 : ft_strlen(s1);
	s2_len = (s2 == NULL) ? 0 : ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (s1_len + s2_len + 2))))
		return (NULL);
	if (s1_len > 0)
		ft_memcpy(str, s1, s1_len);
	str[s1_len] = c;
	if (s2_len > 0)
		ft_memcpy(str + s1_len + 1, s2, s2_len);
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}
