# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/22 12:51:38 by AleXwern          #+#    #+#              #
#    Updated: 2021/01/22 12:51:38 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= script_sender
RECV		= script_recv
FLAGS		= -Wall -Wextra
LIBFT		= ./libft/libft.a
INCLUDES	= -I ./includes -I ./libft/includes

SEND_SRC	= main.c filelist.c data_send.c

RECV_SRC	= main.c data_receive.c

SEND_FILE	= $(addprefix ./src/sender/,$(SEND_SRC))
RECV_FILE	= $(addprefix ./src/receiver/,$(RECV_SRC))
OBJ_SEND	= $(SEND_FILE:.c=.o)
OBJ_RECV	= $(RECV_FILE:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT):
	@echo Compiling Libft libraries.
	@make -C ./libft

$(NAME): $(OBJ_SEND) $(OBJ_RECV) $(LIBFT) $(LIBAX)
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJ_SEND) $(LIBFT)
	@gcc $(FLAGS) $(INCLUDES) -o $(RECV) $(OBJ_RECV) $(LIBFT)
	@mv script_recv ./testenv

clean:
	@/bin/rm -f $(OBJ_SEND)
	@/bin/rm -f $(OBJ_RECV)
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(RECV)
	@make -C ./libft fclean

re: clean all
