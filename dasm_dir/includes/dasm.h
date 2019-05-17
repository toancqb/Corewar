/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 03:50:43 by wta               #+#    #+#             */
/*   Updated: 2019/02/23 03:55:07 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include <inttypes.h>

# define BUFF_SIZE		4096
# define HEADER_SIZE	2192
# define NAME_STR		".name "
# define COMMENT_STR	".comment "
# define NAME_SIZE		128
# define COMMENT_SIZE	2048

typedef enum	e_error
{
	ERR_NOERROR,
	ERR_ERRNO,
	ERR_SIZEHEADER,
	ERR_PROGSIZE,
	ERR_BADTYPE,
	ERR_NBARG,
	ERR_BADOPCODE
}				t_error;

typedef struct	s_op
{
	char			*name;
	int				argc;
	uint8_t			type[3];
	uint8_t			opcode;
	int				cycle;
	char			*long_name;
	unsigned char	encoding	: 1;
	unsigned char	direct		: 1;
}				t_op;

typedef struct	s_data
{
	char		buf[BUFF_SIZE + 1];
	uint32_t	prog_size;
	uint8_t		*inst;
	uint32_t	inst_len;
	char		*filename;
	int			fd;
}				t_data;

t_error			get_header(t_data *data, int fd);
int				get_name(t_data *data, char *filepath);
int				rename_file(char *filename);
int				open_file(t_data *data, char *filepath);
int				create_newfile(t_data *data);

int				manage_argv(t_data *data, t_op *op, uint8_t *byte);
int				inst_manager(t_data *data, uint8_t *byte);
t_error			get_inst(t_data *data, int fd);
t_op			find_op(uint8_t *byte);

int				write_inst(t_data *data);
int				write_indir(t_data *data, uint8_t *byte);
int				write_dire(t_data *data, uint8_t *byte, int direct);
int				write_reg(t_data *data, uint8_t *byte);
uint8_t			write_arg(t_data *data, uint8_t *byte, t_op *op,
		uint8_t encoding);
void			write_header(t_data *data, char *str, int idx, int len);

uint8_t			*ft_memjoin(uint8_t *s1, uint8_t *s2, int s1_len, int s2_len);
uint8_t			*ft_memdup(uint8_t *src, int len);
void			swap_bytes(uint8_t *str, int size);

void			err_handler(t_data *data, t_error id);

#endif
