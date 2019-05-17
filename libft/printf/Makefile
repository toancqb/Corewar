# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2019/02/23 04:39:45 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	printf.a

SRC		=	ft_printf.c parse_tok.c parser.c buffer.c \
			conv_s.c conv_c.c conv_di.c conv_u.c conv_x.c conv_o.c conv_p.c \
			conv_misc.c conv_utils.c
SRC_DIR	=	src

OBJ		=	$(SRC:.c=.o)
OBJ_DIR	=	.obj

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O2 -I ../includes

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/printf.h  | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@/bin/mkdir $@

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
