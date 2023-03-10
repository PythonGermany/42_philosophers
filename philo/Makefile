# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2023/03/10 15:53:56 by rburgsta         ###   ########.fr        #
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