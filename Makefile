# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 12:37:15 by mapoirie          #+#    #+#              #
#    Updated: 2023/10/09 15:34:49 by mapoirie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -pthread -Wall -Wextra -Werror

RM = rm -fr

SRC = philo.c\
philo_utils.c\
thread.c\
routine.c\
eat_routine.c\
time.c\
free.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ)

all : $(NAME)

%.o : %.c
	cc $(FLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re