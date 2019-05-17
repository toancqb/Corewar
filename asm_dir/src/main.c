/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:23:11 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 05:51:29 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include <stdlib.h>

t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0},
	{0, 0, {0, 0, 0}, 0, 0, 0, 0, 0}
};

void		free_data(t_data *data)
{
	int		idx;

	idx = 0;
	while (idx < data->f_size)
	{
		if (data->filter[idx].label != LX_INST)
			ft_strdel(&data->filter[idx].op.name);
		idx += 1;
	}
	lst_free(&data->label_lst);
	ft_strdel(&data->file_name);
	ft_memdel((void **)&data->filter);
}

void		ft_usage(void)
{
	ft_printf("Usage: ./asm  <sourcefile.s>\n");
	ft_printf("\tSupport multiple sourcefile.s\n");
}

t_error		convert_to_asm(t_data *data, t_error err_id, char *str)
{
	ft_memset(data, 0, sizeof(t_data));
	err_id = read_file(str, data);
	if (err_id == ERR_NOERROR)
		err_id = check_valid_tab(data);
	if (err_id == ERR_NOERROR)
		err_id = create_cor(data, str);
	if (err_id == ERR_NOERROR)
		ft_printf("Writing output program to %s\n", data->file_name);
	else
		err_handler(err_id);
	free_data(data);
	return (err_id);
}

int			main(int ac, char **av)
{
	t_data	data;
	t_error err_id;
	int		idx;

	idx = 1;
	err_id = ERR_NOERROR;
	if (ac < 2)
	{
		ft_usage();
		return (0);
	}
	while (idx < ac)
	{
		ft_printf("Compiling champ: %s\n", av[idx]);
		convert_to_asm(&data, err_id, av[idx]);
		err_id = ERR_NOERROR;
		idx++;
		if (idx != ac)
			ft_printf("\n");
	}
	return (0);
}
