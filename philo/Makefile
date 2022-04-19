# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 15:50:59 by jkarosas          #+#    #+#              #
#    Updated: 2022/04/19 11:29:50 by jkarosas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= main.c ft_philosopher.c ft_philosopher_actions.c ft_initialize.c ft_utilities.c ft_check.c
OBJS	= ${SRCS:.c=.o}

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIB		= -lpthread

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIB}

clean:		
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		re fclean clean all