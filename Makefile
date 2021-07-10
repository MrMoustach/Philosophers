# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zed <zed@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/29 10:24:43 by iharchi           #+#    #+#              #
#    Updated: 2021/07/10 14:52:07 by zed              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

SRCS		= srcs/*.c srcs/*/*.c
FLAG		= -Wall -Werror -Wextra

# TODO : CHANGE THIS 
# all: $(NAME)
# $(NAME) : 
all:
			@gcc main.c -g $(SRCS) -o $(NAME) -lpthread
clean:
			@/bin/rm -f $(OBJECT)

fclean: clean
			@/bin/rm -f $(NAME) $(CHECKER)

bonus:

re : fclean all
