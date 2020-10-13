# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/13 11:52:24 by schene            #+#    #+#              #
#    Updated: 2020/10/13 13:27:10 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/ft_putstr.c srcs/main.c srcs/mini_libft.c srcs/philo_handling.c

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

NAME		= philo_one

CC			= clang

CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${FLAGS} ${OBJS}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re