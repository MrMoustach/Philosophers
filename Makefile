# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/29 10:24:43 by iharchi           #+#    #+#              #
#    Updated: 2021/06/28 13:49:19 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

SRCS		= srcs/*.c srcs/*/*.c
FLAG		= -Wall -Werror -Wextra

all: $(NAME)
$(NAME) : 
			@gcc main.c -g $(SRCS) -o $(NAME)
clean:
			@/bin/rm -f $(OBJECT)

fclean: clean
			@/bin/rm -f $(NAME) $(CHECKER)

bonus:

re : fclean all
