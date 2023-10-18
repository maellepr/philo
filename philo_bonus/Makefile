# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 10:11:45 by mapoirie          #+#    #+#              #
#    Updated: 2023/10/18 14:36:09 by mapoirie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

FLAGS = -pthread -Wall -Wextra -Werror

RM = rm -fr

SRC = philo_bonus.c\
philo_utils_bonus.c\
time.c\
process.c\
thread.c\
free.c\
routine.c

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