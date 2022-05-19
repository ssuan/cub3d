# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunbchoi <sunbchoi>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 14:46:27 by sunbchoi          #+#    #+#              #
#    Updated: 2022/05/19 19:18:43 by sunbchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = #-Wall -Wextra -Werror

SRCS = src/main.c\
		src/check.c\
		src/draw.c\
		src/intersection.c\
		src/load.c\
		src/math.c\
		src/mlx.c\
		src/player.c\
		src/ray.c\
		src/render.c\
		src/util.c\
		src/read_cub.c\
		src/read_img.c\
		src/read_rgb.c\
		src/read_map.c\
		src/error.c\

OBJS = $(SRCS:.c=.o)
NAME = cub3D

LIBFT_DIR =	./libft
LIBFT_NAME = libft.a

MINI_DIR = ./minilibx_opengl
MINI_NAME = libmlx.a

INC = -I./minilibx_opengl -I.
LIBS = -L. -lmlx -lft -framework OpenGL -framework Appkit

RM = rm -f

all: $(NAME)

%.o:			%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):	$(MINI_NAME) $(LIBFT_NAME) $(OBJS)
			$(CC) $(CFLAG) $(INC) -o $@ $(OBJS) $(LIBS)

$(MINI_NAME):
	make -C $(MINI_DIR)
	mv $(MINI_DIR)/$(MINI_NAME) .
	
$(LIBFT_NAME):
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/$(LIBFT_NAME) .

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