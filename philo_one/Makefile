# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/13 11:52:24 by schene            #+#    #+#              #
#    Updated: 2020/10/17 16:30:50 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/ft_putstr.c srcs/main.c srcs/ft_utils.c srcs/philo_handling.c \
				srcs/time_management.c srcs/philo_life.c  

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

NAME		= philo_one

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