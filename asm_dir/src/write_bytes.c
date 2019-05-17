/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 04:22:34 by qtran             #+#    #+#             */
/*   Updated: 2019/02/18 05:15:40 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <inttypes.h>
#include "op.h"
#include "asm.h"

void	swap_bytes(unsigned char *str, int size)
{
	unsigned char	tmp;
	int				i;

	i = 0;
	while (i < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
		i++;
	}
}

void	write_magic(uint8_t *ptr, int fd, int len)
{
	int		idx;

	idx = 0;
	while (idx < len)
	{
		if (ptr[idx] > 0)
			write(fd, &ptr[idx], 1);
		idx += 1;
	}
}

void	write_encoding_byte(t_op *op, int fd)
{
	uint8_t	encoding_byte;
	uint8_t	dire;
	uint8_t	ind;
	uint8_t	reg;
	int		idx;

	reg = 0x1;
	dire = 0x2;
	ind = 0x3;
	idx = 0;
	encoding_byte = 0;
	while (idx < 3)
	{
		if (op->type[idx] & T_DIR)
			encoding_byte |= dire;
		else if (op->type[idx] & T_IND)
			encoding_byte |= ind;
		else if (op->type[idx] & T_REG)
			encoding_byte |= reg;
		encoding_byte <<= 2;
		idx += 1;
	}
	write(fd, &encoding_byte, 1);
}
