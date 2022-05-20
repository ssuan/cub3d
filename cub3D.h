/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:44:19 by suan              #+#    #+#             */
/*   Updated: 2022/05/20 14:03:41 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "mlx.h"

# define ITEM_KEY "10NEWS"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define DIR_N 0
# define DIR_E 1
# define DIR_W 2
# define DIR_S 3 

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

# define SUCCESS 0
# define FAIL 1

# define TRUE 1
# define FALSE 0

# define  MAPX   5
# define  MAPY   6
# define  SX         300     /* screen width */
# define  SY         250     /* screen height */
# define  FOV        60      /* field of view (in degree) */
# define  WALL_H     1.0

# define VERT 0
# define HORIZ 1

# define  _2PI       6.28318530717958647692  /* 2 * M_PI */

# define  ROT_UNIT   0.03    /* rad */
# define  MOVE_UNIT  0.1

typedef struct s_player {
	double	px;
	double	py;
	double	th;
}	t_player;

typedef struct s_pos {
	double	x;
	double	y;
}	t_pos;

typedef struct s_img {
	void			*img;
	char			*addr;
	unsigned int	*data;
	int				w;
	int				h;
	int				bpp;
	int				size_l;
	int				endian;
}	t_img;

typedef struct s_intersect {
	int		xstep;
	int		ystep;
	double	xslope;
	double	yslope;
	double	f;
	double	g;
	int		mapx;
	int		mapy;
	double	dist_v;
	double	dist_h;
	int		hit_side;
}	t_intersect;

typedef struct s_map {
	int		floor_color;
	int		ceil_color;
	char	map[1000][1000];
	char	chk[1000][1000];
	int		mapx;
	int		mapy;
}	t_map;

typedef struct s_game {
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	double		fov_h;
	double		fov_v;
	double		per_angle;
	t_map		map;
	t_img		wall[4];
	t_player	pl;
	t_pos		wpos;
	int			wdir;
}	t_game;

// init
int		init_game(t_game *game);

// check
char	map_get_cell(t_game *game, int x, int y);
void	map_check(t_game *game);
int		input_check(int ac, char **av);

// draw
void	draw(t_game *game, double wdist, int x);

// intersection
int		get_wall_intersection(t_game *game, double ray);

// load
void	load_image(t_game *game, t_img *img, char *path);

//read
void	read_cub(char *cub, t_game *game);
int		read_img(int fd, t_game *game);
int		read_map(int fd, t_game *game);
int		read_rgb(int fd, t_game *game);
int		empty_line_check(char *line_empty);
char	*not_empty_line_load(int fd);

//error
int		error(char *msg);

// math
int		min(int a, int b);
int		max(int a, int b);

// mlx
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// player
void	player_rotate(t_player *pl, double th);
int		player_move(t_game *game, int key, double amt);

// ray
double	cast_single_ray(t_game *game, int x);

// render
void	render(t_game *game);

// util 
double	l2dist(double x0, double y0, double x1, double y1);
int		is_zero(double d);
int		sgn( double d );
double	deg2rad(double degree);
double	rad2deg(double radian);

#endif