# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/13 19:57:51 by tide-jon       #+#    #+#                 #
#    Updated: 2019/06/15 16:28:37 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#			DIT MAAKT NU EEN EXECUTABLE 'TEST' - VERANDEREN NAAR LIBRARY MAKEN MET RC EN RANLIB!
NAME =		test

SRCS = 		ft_printf.c conv_csp.c conv_di.c conv3.c conv_u.c conv_o.c

OBJECTS =	$(SRCS:.c=.o)

all :		$(NAME)

$(NAME) :	$(OBJECTS)
			@ cd libft && make && cd ..
			@ gcc -Wall -Wextra -Werror $(OBJECTS) -L ./libft/ -lft -o $(NAME)

%.o : %.c
			@ gcc -c -Wall -Wextra -Werror $< -o $@ -I ./libft/

clean :
			@ cd libft && make clean && cd .. && rm -f $(OBJECTS)

fclean :
			@ cd libft && make fclean && cd .. && \
			rm -f $(OBJECTS) && rm -f $(NAME)

re :		fclean all
