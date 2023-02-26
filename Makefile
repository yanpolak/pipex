# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 17:21:56 by ymarival          #+#    #+#              #
#    Updated: 2023/02/12 20:45:59 by ymarival         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC			= 	pipex.c pipex_utils.c\

SRCB			=	pipex_bonus.c pipex_utils_bonus.c\
					
OBJ			= $(SRC:.c=.o)

OBJB			= $(SRCB:.c=.o)

NAME			= pipex

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror 


RM				= rm -f


all:			$(NAME)

$(NAME):		$(OBJ) 
				${CC} ${CFLAGS} -o $(NAME) $(OBJ) 

clean:
				$(RM) $(OBJ) $(OBJB) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:		$(OBJB)
			${CC} ${CFLAGS} -o $(NAME) $(OBJB)

.PHONY:			all clean fclean re bonus
