# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

SRC_DIR		=	src
SRC			=			\
main.c					\
options.c				\
options_utils.c			\
read.c					\
champs.c				\
champs_utils.c			\
cycles.c				\
process.c				\
errors.c				\
print_arena.c			\
pc_utils.c				\
op/op_utils.c			\
op/op_utils2.c			\
op/live.c				\
op/ld.c					\
op/st.c					\
op/add.c				\
op/sub.c				\
op/ft_and.c				\
op/ft_or.c				\
op/ft_xor.c				\
op/zjmp.c				\
op/ldi.c				\
op/sti.c				\
op/ft_fork.c			\
op/lld.c				\
op/lldi.c				\
op/ft_lfork.c			\
op/aff.c				\
visual/func_print.c		\
visual/init_ncurses.c	\
visual/print_hud.c		\
visual/print_champ.c	\
visual/key_hook.c		\
visual/math_utils.c		\
visual/sig_handler.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)
INC_DIR	=	includes

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I ../libft/includes -I $(INC_DIR)

LIBFT	=	../libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -lncurses -o $@ $^

$(LIBFT):
	@$(MAKE) -C ../libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@/bin/mkdir $@
	@/bin/mkdir $@/op
	@/bin/mkdir $@/visual

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
