# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 14:46:27 by sunbchoi          #+#    #+#              #
#    Updated: 2021/11/25 17:42:40 by sunbchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = -Wall -Wextra -Werror

SRCS = src/main.c\
		src/check_area.c\
		src/error.c\
		src/initialize.c\
		src/print_map.c\
		src/process_game.c\
		src/validate_map.c\
		
OBJS = $(SRCS:.c=.o)
NAME = so_long
LIBFT_DIR =	./libft
LIBFT_NAME = libft.a
MINI_DIR = ./minilibx_opengl
MINI_NAME = libmlx.a
HEADER = -I /minilibx_2020
LIBS		=-L. -lmlx -lft -framework OpenGL -framework Appkit

RM = rm -f

all: $(NAME)

$(NAME):	$(MINI_NAME) $(LIBFT_NAME) $(OBJS) 
			$(CC) $(CFLAG) $(HEADER) -o $@ $(OBJS) $(LIBS)

$(MINI_NAME):
	make -C $(MINI_DIR)
	mv $(MINI_DIR)/$(MINI_NAME) .
	
$(LIBFT_NAME):
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/$(LIBFT_NAME) .
	
%o:			%.c
			$(CC) $(CFLAGS)  -c $< -o $@

clean:
			$(RM) $(OBJS)
			make clean -C $(LIBFT_DIR)
			make clean -C $(MINI_DIR)

fclean:
			make clean
			$(RM) $(MINI_NAME)
			$(RM) $(LIBFT_NAME)
			$(RM) $(NAME)

re:
			make fclean all

.PHONY:		all clean fclean re