# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2023/01/30 18:56:29 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror #-pthread
LK_SAN = #-Wno-gnu-include-next -I/LeakSanitizer/include -L../../LeakSanitizer/ -llsan -lc++

SRC = main.c init.c routine.c monitoring.c
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(LK_SAN) -o $(NAME) $(OBJ)

%.o : %.c
	cc -c $(FLAGS) $^

b : $(NAME) clean
	clear

val : bin

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all