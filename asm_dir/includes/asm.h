/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:25:14 by qtran             #+#    #+#             */
/*   Updated: 2019/02/23 05:36:36 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <inttypes.h>
# include "op.h"
# include "libft.h"

typedef	enum	e_error
{
	ERR_NOERROR,
	ERR_ARGNB,
	ERR_ERRNO,
	ERR_BADFMT,
	ERR_NOINST,
	ERR_NOLABEL,
	ERR_GNL,
	ERR_NAME_LENGTH,
	ERR_COMMENT_LENGTH,
	ERR_DUPLABEL,
	ERR_HEADER,
	ERR_MALLOC
}				t_error;

typedef struct	s_list_ref
{
	t_list		*head;
	t_list		*tail;
}				t_list_ref;

typedef struct	s_op
{
	char					*name;
	int						argc;
	uint8_t					type[3];
	uint8_t					opcode;
	int						cycle;
	char					*long_name;
	unsigned char			encoding	: 1;
	unsigned char			direct		: 1;
}				t_op;

typedef	enum	e_lexer
{
	LX_INST,
	LX_REG,
	LX_DIRE,
	LX_ERROR,
	LX_INDIR,
	LX_COMMENT,
	LX_SIX,
	LX_SEVEN,
	LX_LABEL
}				t_lexer;

typedef struct	s_filter
{
	t_op			op;
	t_lexer			label;
	int				size;
	int				value;
	int				index;
}				t_filter;

typedef struct	s_data
{
	t_header	header;
	t_list_ref	label_lst;
	t_filter	*filter;
	int			f_size;
	char		*file_name;
}				t_data;

void			ft_usage(void);
t_error			convert_to_asm(t_data *data, t_error err_id, char *str);
t_error			read_file(char *file, t_data *data);
void			set_op_tab(t_op op_tab[]);

int				get_filter(char *str, t_filter *filter, t_lexer lex_id);
int				get_tab_size(char **tab);

t_lexer			check_if_valid(char *str, char **inst);
t_error			check_first_line(int fd);
t_error			check_endline(char *str);
int				is_int(char *str);
t_filter		*is_label(char *str, t_list *head);
char			*get_dquote(char *str);
t_error			skip_useless(int fd, char **line);
char			*skip_tab_n_space(char *str);

void			lst_pushback(t_list_ref *list, t_list *node);
t_list			*lstnew_mallocfree(void *content);
void			lst_free(t_list_ref *list);

void			init_inst(t_data *data);

t_error			check_valid_tab(t_data *data);
t_error			classify(t_data *data, char **split);
t_error			create_cor(t_data *data, char *str);

void			lst_pushback(t_list_ref *list, t_list *node);
t_list			*lstnew_mallocfree(void *content);
t_error			lst_lab_check(t_list_ref *list, t_list *node);

void			swap_bytes(unsigned char *str, int size);
void			write_magic(uint8_t *ptr, int fd, int len);
void			write_encoding_byte(t_op *op, int fd);

t_error			fill_prog_name(t_data *data, int fd, char **str, char **line);
t_error			get_name(t_data *data, int fd, char **line);
t_error			fill_comment(t_data *data, int fd, char **str, char **line);

char			*get_file_name(char *str);
t_error			get_comment(t_data *data, int fd, char **line);
void			fill_header(t_data *data, int fd);
t_error			fill_instruction(t_data *data, int fd);

int				manage_filter(t_filter *elem, t_data *data, int fd);
int				manage_inst(t_filter *inst, t_data *data, int fd);
void			manage_label(t_filter *inst, t_filter *arg
			, t_filter *label, int fd);
void			manage_dir(t_filter *inst, t_filter *arg, int fd);
void			manage_ind(t_filter *arg, int fd);

int				replace_mod(char *str, char *new);
int				replace_colon(char *str, char *new);

void			expand_space(char *str, char *new, int len);
char			*expand_label(char *str);

char			*strjoin_add_c(char const *s1, char const *s2, char c);
char			**split_by_str(char *str, char *delim);
int				cnt_space_to_add(char *str);

void			free_split_n_line(char **line, char ***split, int fd);
void			err_handler(t_error err_id);
t_error			err_print(char *str, t_error err_id);

#endif
