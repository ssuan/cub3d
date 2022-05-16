# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 14:46:27 by sunbchoi          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/05/16 21:58:55 by sunbchoi@st      ###   ########.fr        #
=======
#    Updated: 2022/05/16 20:29:05 by suan             ###   ########.fr        #
>>>>>>> 124e741fd2fcc262e83ef4e71bae5341d70ea17d
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = #-Wall -Wextra -Werror

SRCS = src/main.c\
		src/player.c\
		src/ray.c\
		src/draw.c\
		src/util.c\
		src/intersection.c\
<<<<<<< HEAD
		src/read_cub.c\
		src/read_img.c\
		src/read_rgb.c\
		src/read_map.c\
		src/error.c\
=======
		src/check.c\
		src/load.c\
		src/render.c\
		src/mlx.c\
>>>>>>> 124e741fd2fcc262e83ef4e71bae5341d70ea17d

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