/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 03:43:01 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 02:19:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "stdlib.h"
#include "unistd.h"
#include "libft.h"
#include "dasm.h"

t_op	g_op_tab[17] =
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

t_error	deassemble(t_data *data, int fd)
{
	t_error	err_id;

	err_id = get_header(data, fd);
	if (err_id == ERR_NOERROR)
		err_id = get_inst(data, fd);
	close(fd);
	if (data->prog_size != data->inst_len)
		err_id = ERR_PROGSIZE;
	if (err_id == ERR_NOERROR)
		err_id = write_inst(data);
	free(data->inst);
	close(data->fd);
	return (err_id);
}

int		main(int ac, char **av)
{
	t_data	data;
	t_error	err_id;
	int		fd;

	if (ac == 2)
	{
		err_id = ERR_NOERROR;
		ft_memset(&data, 0, sizeof(t_data));
		if ((fd = open_file(&data, av[1])) == -1)
			err_id = ERR_ERRNO;
		if (err_id == ERR_NOERROR)
			err_id = create_newfile(&data);
		if (err_id == ERR_NOERROR)
			err_id = deassemble(&data, fd);
	}
	else
		err_id = ERR_NBARG;
	err_handler(&data, err_id);
	return (0);
}
