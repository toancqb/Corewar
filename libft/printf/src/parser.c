/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 23:19:42 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/10 19:39:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

static int	pf_ptok(t_pf *pf, const char **tok)
{
	if (**tok == '#' || **tok == '0' || **tok == '-'
			|| **tok == ' ' || **tok == '+')
		return (pf_flag(pf, tok));
	else if (**tok == 'L' || **tok == 'j' || **tok == 'z'
			|| **tok == 'h' || **tok == 'l')
		return (pf_modifier(pf, tok));
	else if (**tok == '.')
		return (pf_precision(pf, tok));
	else if (**tok == '*' || (**tok >= '0' && **tok <= '9'))
		return (pf_w_field(pf, tok));
	return (0);
}

static void	pf_conv_type(t_pf *pf)
{
	if (pf->type == 'S' || pf->type == 'C'
			|| pf->type == 'D' || pf->type == 'O' || pf->type == 'U')
	{
		pf->type = ft_tolower(pf->type);
		pf->flags &= ~(LUP_MODIFIER | J_MODIFIER | Z_MODIFIER
				| H_MODIFIER | L_MODIFIER | HH_MODIFIER | LL_MODIFIER);
		pf->flags |= L_MODIFIER;
	}
	if (pf->type == 's')
		pf_conv_s(pf);
	else if (pf->type == 'c')
		pf_conv_c(pf);
	else if (pf->type == 'd' || pf->type == 'i')
		pf_conv_di(pf);
	else if (pf->type == 'u')
		pf_conv_u(pf);
	else if (pf->type == 'x' || pf->type == 'X')
		pf_conv_x(pf);
	else if (pf->type == 'o')
		pf_conv_o(pf);
	else if (pf->type == 'p')
		pf_conv_p(pf);
	else
		pf_conv_misc(pf);
}

void		pf_parse(t_pf *pf, const char *fmt)
{
	const char	*tok;
	size_t		off;

	tok = ft_strchr(fmt, '%');
	if (tok == NULL)
		buf_write(pf, fmt, ft_strlen(fmt));
	else
	{
		off = (size_t)(tok - fmt);
		if (off > 0)
			buf_write(pf, fmt, off);
		tok++;
		pf->flags = 0;
		pf->w_field = -1;
		pf->precision = -1;
		while (pf_ptok(pf, &tok))
			continue ;
		pf->type = *tok;
		if (*tok == '\0')
			return ;
		pf_conv_type(pf);
		pf_parse(pf, tok + 1);
	}
}
