/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:44:19 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 13:45:06 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"

# define ITEM_KEY "10CPE"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53

# define SUCCESS 1
# define FAILURE 0

#define TILES 60
#define COL 15
#define ROW 15
#define WIDTH TILES * COL
#define HEIGHT TILES * ROW

//
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */ -> 함수

#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))


#define  MAPX   6
#define  MAPY   5
#define  SX         300     /* screen width */
#define  SY         250     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define  _2PI       6.28318530717958647692  /* 2 * M_PI */

#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1

typedef struct {
	double px;
	double py;
	double th;
} player_t;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	player_t pl;
	t_data	img;
} t_game;

#endif