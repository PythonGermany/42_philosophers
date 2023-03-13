# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2023/03/13 14:07:18 by rburgsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror

SRC = main.c init.c routine.c output.c
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(LK_SAN) -o $(NAME) $(OBJ)

%.o : %.c
	cc -c $(FLAGS) $^

bin : $(NAME) clean
	clear

git : 
	git add Makefile *.c *.h
	git status
	git commit -m $(msg)
	git push

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all