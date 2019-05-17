# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/02/23 04:43:54 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	dasm

SRC_DIR	=	src
SRC		=		\
dasm_helpers.c	\
error.c			\
main.c			\
manage_header.c	\
utils.c			\
write.c			\
write_2.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)

INC_DIR	=	includes

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I ../libft/includes -I $(INC_DIR)

LIBFT	=	../libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -o $@ $^

$(LIBFT):
	@$(MAKE) -C ../libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@/bin/mkdir $@

clean:
	@echo "Cleaning $(NAME)"
	@$(MAKE) -C ../libft clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Full clean $(NAME)"
	@$(MAKE) -C ../libft fclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
