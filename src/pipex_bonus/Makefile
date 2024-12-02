# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphox <raphox@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 15:01:28 by raphox            #+#    #+#              #
#    Updated: 2024/12/02 17:48:35 by raphox           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

SRCS			=	pipex_bonus.c my_split.c build_command.c tools.c  builtins.c tools_built.c check_redirections.c \

OBJS			=	${SRCS:.c=.o}

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -g3 -g

LIBFT_DIR	=	../lib/libft

LIBFT_LIB	=	$(LIBFT_DIR)

all			:	${NAME}

$(NAME): $(OBJS) $(LIBFT_LIB)
	make -C ${LIBFT_DIR}
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@mkdir -p ../obj/pipex_bonus
	cp pipex_bonus.o ../obj/pipex_bonus/
	cp tools.o ../obj/pipex_bonus/
	cp split.o ../obj/pipex_bonus/



clean			:
	rm -rf ${OBJS}
	make -C ${LIBFT_DIR} clean

fclean			:	clean
	rm -rf ${NAME}
	make -C ${LIBFT_DIR} fclean

re				:	fclean all

.PHONY			:	all clean fclean re