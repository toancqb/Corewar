/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 06:08:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

void		swap_bytes(uint8_t *str, int size)
{
	int		idx;
	uint8_t	tmp;

	idx = 0;
	while (idx < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[idx];
		str[idx] = tmp;
		idx++;
	}
}

/*
** Rempli un buffer depuis un zone de l'arene.
** ATTENTION : N'applique pas de swap_bytes.
*/

void		fill_buff_from_arena(t_env *env, uint8_t *buffer, size_t size
		, int offset)
{
	fix_pc_offset(&offset);
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(buffer, env->arena + offset, size);
	else
	{
		ft_memcpy(buffer, env->arena + offset, MEM_SIZE - offset);
		ft_memcpy((buffer + MEM_SIZE - offset), env->arena
				, size - MEM_SIZE + offset);
	}
}

/*
** Ecrit de facon circulaire dans l'arene.
** ATTENTION : Les donnes sont swap avant d'etre ecrites.
*/

void		write_in_arena(t_env *env, uint8_t *bytes, size_t size, int offset)
{
	fix_pc_offset(&offset);
	swap_bytes(bytes, size);
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(env->arena + offset, bytes, size);
	else
	{
		ft_memcpy(env->arena + offset, bytes, MEM_SIZE - offset);
		ft_memcpy(env->arena, bytes + (MEM_SIZE - offset)
				, size - MEM_SIZE + offset);
	}
	swap_bytes(bytes, size);
}

static int	decode_arg(t_arg *arg, uint8_t *args, uint8_t encoding_byte
		, int dir_size)
{
	if ((encoding_byte & 0xC0) == 0x40)
	{
		arg->type = REG_CODE;
		arg->value = *((int8_t *)args);
		if ((int)arg->value < 1 || (int)arg->value > 16)
			arg->type = BAD_REG;
		return (1);
	}
	else if ((encoding_byte & 0xC0) == 0xC0
			|| ((encoding_byte & 0xC0) == 0x80 && dir_size == SHORT_DIR))
	{
		arg->type = ((encoding_byte & 0xC0) == 0xC0) ? IND_CODE : DIR_CODE;
		swap_bytes(args, 2);
		arg->value = *((int16_t *)args);
		return (2);
	}
	else if ((encoding_byte & 0xC0) == 0x80)
	{
		arg->type = DIR_CODE;
		swap_bytes(args, 4);
		arg->value = *((int32_t *)args);
		return (4);
	}
	return (0);
}

/*
** Parse les arguments d'une instruction grace a l'octet d'encodage envoye
** en deuxieme parametre. Permet de specifier une taille pour les types DIR.
** Renvoie le nombre d'octets correspondant a l'encoding byte.
*/

int			decode_args(t_decode *decode, uint8_t *args, uint8_t encoding_byte
		, int dir_size)
{
	int	idx;
	int	ret;
	int	arg_ret;

	idx = 0;
	ret = 0;
	while (idx < decode->max_args)
	{
		arg_ret = decode_arg(decode->tab + idx, args, encoding_byte, dir_size);
		ret += arg_ret;
		args += arg_ret;
		encoding_byte <<= 2;
		idx++;
	}
	return (ret);
}
