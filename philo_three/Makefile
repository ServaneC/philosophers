# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:55:40 by schene            #+#    #+#              #
#    Updated: 2020/10/28 15:10:30 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/main.c srcs/ft_print.c srcs/ft_utils.c srcs/philo_life.c \
				srcs/struct_management.c srcs/time_management.c \
				srcs/print_statements.c srcs/monitor.c srcs/sem.c

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

NAME		= philo_three

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -pthread

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${FLAGS} ${OBJS}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re