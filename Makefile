# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laroges <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 01:52:45 by laroges           #+#    #+#              #
#    Updated: 2024/03/15 15:18:26 by laroges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
	init.c \
	minishell.c \
	path.c \
	builtin.c \
	ft_pwd.c \
	execute.c \
	free.c \

CC =	gcc

CFLAGS = -Wall -Werror -Wextra

OBJ =	$(SRC:.c=.o)

NAME =	./minishell

NAMELIBFT =	libft.a

INCLUDELIBFT =	./libft/

all: $(NAME)

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -I $(INCLUDELIBFT) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	cp $(INCLUDELIBFT)$(NAMELIBFT) .
	$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDELIBFT) $(NAMELIBFT) -o $(NAME) -lreadline

clean:
	make clean -C libft
	rm -f $(OBJ) $(NAMELIBFT) $(INCLUDELIBFT)$(NAMELIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
