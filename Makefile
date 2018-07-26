# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/22 22:52:53 by jjolivot          #+#    #+#              #
#    Updated: 2018/07/25 20:06:33 by jjolivot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

LIB = includes/libft/libft.a

SRC = src/main.c src/ft_ls.c src/ft_inspect_file.c src/ft_sort.c

INC = includes/ls.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C includes/libft re
	$(CC) $(CFLAGS) $(LIB) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all
