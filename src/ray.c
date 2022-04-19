#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
# define ROW        11
# define COL        15
# define TILE_SIZE    32
# define WIDTH        COL * TILE_SIZE
# define HEIGHT        ROW * TILE_SIZE
 
# define KEY_ESC    53

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

# define KEY_EVENT_PRESS    2
# define KEY_EVENT_EXIT        17

# define PI    3.14159265359
 
typedef struct	s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_size;
	int		endian;
} t_img;
 
typedef struct	s_pos
{
	double	x;
	double	y;
} t_pos;

typedef struct	s_vec2
{
	double	x;
	double	y;
} t_vec2;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	int		map[ROW][COL];
	t_img	map_img;
	t_img	img;
	t_pos	pos;
	t_vec2	dir_vec;
} t_game;
 
 
void    draw_dir_ray(t_game *game, double angle)
{
	double    ray_x;
	double    ray_y;
	double    dx;
	double    dy;
	double    max_value;
 
	ray_x = game->pos.x;
	ray_y = game->pos.y;
 
	dx = cos(angle) * game->dir_vec.x - sin(angle) * game->dir_vec.y;
	dy = sin(angle) * game->dir_vec.x + cos(angle) * game->dir_vec.y;
 
	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (game->map_img.data[WIDTH * (int)floor(ray_y) + (int)floor(ray_x)] != 0x0000FF)
			game->map_img.data[WIDTH * (int)floor(ray_y) + (int)floor(ray_x)] = 0xFF0000;
		else
			break;
		ray_x += dx;
		ray_y += dy;
	}
}
 
void    draw_ray(t_game *game)
{
	double angle;
 
	angle = 0;
	while (angle < PI/6)
	{
		draw_dir_ray(game, angle);
		draw_dir_ray(game, -angle);
		angle += PI/72;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->map_img.img, 0, 0);
}
 
void    rotate_matrix(t_vec2 *vec, double angle)
{
	double    tmp_x;
 
	tmp_x = cos(angle) * vec->x - sin(angle) * vec->y;
	vec->y = sin(angle) * vec->x + cos(angle) * vec->y;
	vec->x = tmp_x;
}
 
int        key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_LEFT)
		rotate_matrix(&game->dir_vec, PI/36);
	if (keycode == KEY_RIGHT)
		rotate_matrix(&game->dir_vec, -PI/36);
	if (keycode == KEY_DOWN)
	{
		game->pos.x -= game->dir_vec.x * 0.05;
		game->pos.y -= game->dir_vec.y * 0.05;
	}
	if (keycode == KEY_UP)
	{
		game->pos.x += game->dir_vec.x * 0.05;
		game->pos.y += game->dir_vec.y * 0.05;
	}
	return (0);
}
 
int        exit_button(void)
{
	exit(0);
}
 
void    draw_square(t_game *game, int x, int y, int color)
{
	int dx;
	int dy;
 
	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			game->img.data[WIDTH * (y + dy) + (x + dx)] = color;
			dx++;
		}
		dy++;
	}
}
 
void    draw_squares(t_game *game)
{
	int x;
	int y;
 
	y = 0;
	while (y < ROW)
	{
		x = 0;
		while (x < COL)
		{
			if (game->map[y][x] == 1)
				draw_square(game, TILE_SIZE * x, TILE_SIZE * y, 0x0000FF);
			else
				draw_square(game, TILE_SIZE * x, TILE_SIZE * y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}
 
void    draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double    deltaX;
	double    deltaY;
	double    step;
 
	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[(int)floor(y1) * WIDTH + (int)floor(x1)] = 0xC0C0C0;
		x1 += deltaX;
		y1 += deltaY;
	}
}
 
void    draw_lines(t_game *game)
{
	int i;
 
	i = 0;
	while (i <= ROW)
	{
		draw_line(game, 0, TILE_SIZE * i, WIDTH, TILE_SIZE * i);
		i++;
	}
	i = 0;
	while (i <= COL)
	{
		draw_line(game, TILE_SIZE * i, 0, TILE_SIZE * i, HEIGHT);
		i++;
	}
}
 
int        draw_loop(t_game *game)
{
	draw_squares(game);
	draw_lines(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
 
int        main(void)
{
	int map[ROW][COL] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	t_game    game;
 
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "2D_MAP");
	memcpy(game.map, map, sizeof(int) * ROW * COL);
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.data = (int *)mlx_get_data_addr(game.img.img,
						&game.img.bpp, &game.img.line_size, &game.img.endian);
	game.map_img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.map_img.data = (int *)mlx_get_data_addr(game.img.img,
						&game.img.bpp, &game.img.line_size, &game.img.endian);
	game.pos.x = 200;
	game.pos.y = 200;

	mlx_hook(game.win, KEY_EVENT_PRESS, 0, key_press, &game);
	mlx_hook(game.win, KEY_EVENT_EXIT, 0, exit_button, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
 
	mlx_loop(game.mlx);
	return (0);
}