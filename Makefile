# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/13 19:57:51 by tide-jon       #+#    #+#                 #
#    Updated: 2019/06/21 22:01:39 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

SRCS = 		ft_printf.c conv_csp.c conv_di.c conv3.c conv_u.c conv_o.c conv_x.c conv_prcnt.c conv_f.c

OBJECTS =	$(SRCS:.c=.o)

all :		$(NAME)

$(NAME) :
			@ cd libft && make && cd ..
			@ mv ./libft/libft.a $(NAME)
			@ gcc -Wall -Wextra -Werror -c $(SRCS) -I ./libft/
			@ ar rc $(NAME) $(OBJECTS)
			@ ranlib $(NAME)
			@ echo "Library succesfully created"

clean :
			@ cd libft && make clean && cd .. && rm -f $(OBJECTS)
			@ echo "Clean completed"

fclean :
			@ cd libft && make fclean && cd .. && \
			rm -f $(OBJECTS) && rm -f $(NAME)
			@ echo "Clean completed"

re :		fclean all
