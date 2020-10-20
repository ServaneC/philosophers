# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/19 16:53:25 by schene            #+#    #+#              #
#    Updated: 2020/10/20 10:34:47 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

NAME		= philo_two

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -pthread -lrt

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${FLAGS} ${OBJS}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re