/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/23 05:38:32 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_arg(t_data *data, int i)
{
	t_filter	*arg;
	t_lexer		id;
	char		*endptr;
	int			n;

	n = -1;
	while (++n < data->filter[i].op.argc && (i + 1 + n) < data->f_size)
	{
		arg = &data->filter[i + 1 + n];
		id = arg->label;
		if (id == LX_DIRE)
			arg->op.direct = data->filter[i].op.direct;
		if ((id & data->filter[i].op.type[n]) == 0)
		{
			ft_dprintf(2, "Error: arg bad type: \"%s\" from inst \"%s\"\n",
					arg->op.name, data->filter[i].op.name);
			return (-1);
		}
		data->filter[i].op.type[n] &= id;
		if (id == LX_DIRE || id == LX_REG)
			arg->value = (int)ft_strtol(arg->op.name + 1, &endptr, 10);
		else if (id == LX_INDIR)
			arg->value = (int)ft_strtol(arg->op.name, &endptr, 10);
	}
	return (n + 1);
}

static t_error	check_is_label(t_data *data)
{
	char	*name;
	char	*arg;
	int		offset;
	int		idx;
	int		jdx;

	idx = -1;
	while (++idx < data->f_size)
	{
		name = data->filter[idx].op.name;
		jdx = -1;
		if (ft_strnequ(name, "%:", 2) || *name == ':')
		{
			offset = 1 + (*name != ':');
			while (++jdx < data->f_size)
			{
				arg = data->filter[jdx].op.name;
				if (ft_strnequ((name + offset), arg, ft_strlen(name + offset)))
					break ;
			}
		}
		if (jdx == data->f_size)
			return (err_print(name, ERR_NOLABEL));
	}
	return (ERR_NOERROR);
}

static void		set_size(t_filter *filter)
{
	if (filter->label == LX_INST && filter->op.encoding == 1)
		filter->size = 2;
	else if (filter->label == LX_INST)
		filter->size = 1;
	else if (filter->label == LX_REG)
		filter->size = 1;
	else if (filter->label == LX_DIRE && filter->op.direct == 1)
		filter->size = 2;
	else if (filter->label == LX_DIRE)
		filter->size = 4;
	else if (filter->label == LX_INDIR)
		filter->size = 2;
}

static t_error	set_label_size(t_data *data)
{
	t_list			*node;
	unsigned int	size;
	int				i;

	i = 0;
	size = 0;
	while (i < data->f_size)
	{
		data->filter[i].size = 0;
		data->filter[i].index = size;
		if (data->filter[i].label == LX_LABEL)
		{
			if ((node = lstnew_mallocfree(&data->filter[i].op)) == NULL)
				return (ERR_MALLOC);
			if (lst_lab_check(&data->label_lst, node) == ERR_DUPLABEL)
				return (err_print(data->filter[i].op.name, ERR_DUPLABEL));
		}
		else if (data->filter[i].label == LX_ERROR)
			return (err_print(data->filter[i].op.name, ERR_BADFMT));
		set_size(&data->filter[i]);
		size += data->filter[i].size;
		i++;
	}
	data->header.prog_size = size;
	return (ERR_NOERROR);
}

t_error			check_valid_tab(t_data *data)
{
	int		idx;
	int		jdx;

	idx = 0;
	jdx = 0;
	while (idx < data->f_size)
	{
		if (data->filter[idx].label == LX_INST)
		{
			if (idx + 1 >= data->f_size || (jdx = check_arg(data, idx)) == -1)
				return (ERR_BADFMT);
			idx += jdx;
		}
		else if (data->filter[idx].label == LX_LABEL)
			idx += 1;
		else
			return (err_print(data->filter[idx].op.name, ERR_BADFMT));
	}
	if (check_is_label(data) != ERR_NOERROR)
		return (ERR_NOLABEL);
	return (set_label_size(data));
}
