# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/29 10:24:43 by iharchi           #+#    #+#              #
#    Updated: 2021/09/15 17:37:40 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

SRCS		=	srcs/actions.c\
				srcs/philo.c\
				srcs/runtime.c\
				srcs/wrappers.c\
				srcs/clist/clist.c\
				srcs/utils/ft_atol.c\
				srcs/utils/ft_utils.c
FLAG		= -Wall -Werror -Wextra -lpthread

OBJECTS		=	
all: $(NAME)
$(NAME):
			@gcc main.c -g $(SRCS) -o $(NAME) 
clean:
			@/bin/rm -f $(OBJECT)

fclean: clean
			@/bin/rm -f $(NAME)

bonus:

re : fclean all
