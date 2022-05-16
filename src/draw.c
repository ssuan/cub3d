/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:27:37 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 16:13:29 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 나중에 빼기
/* DIR_N, E, W, S */
int	g_wall_colors[] = {
		0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
	};

//mlx
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* distance to the floor-FOV intersection point */
static double	get_fov_min_dist(t_game *game)
{
	static double	T = -1;

	if (T < 0)
		T = WALL_H / (2.0 * tan(game->fov_v / 2.0));
	return (T);
}

#define COLOR_FLOOR 0x00d3c6a6
#define COLOR_CEIL  0x006df6ea
static void	draw_floor_and_ceil(t_game *game, int x, int y1)
{
	int		y;
	double	ec;
	double	h;
	double	d;

	if (y1 < SY - 1)
	{
		ec = get_fov_min_dist(game);
		y = y1; // y = y1 + 1
		while (y < SY)
		{
			h = (double)(SY - 1 - y) / SY;
			d = ec / (1. - 2 * h);
			my_mlx_pixel_put(&(game->img), x, y, COLOR_FLOOR);
			my_mlx_pixel_put(&(game->img), x, (SY - 1 - y), COLOR_CEIL);
			y++;
		}
	}
}

static int	get_wall_height(t_game *game, double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(game->fov_v / 2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}

//wall
static void	draw_wall(t_game *game, double wdist, int x, int color)
{
	int	wh;
	int	y0;
	int	y1;
	int	ystart;
	int	yend;

	wh = get_wall_height(game, wdist);
	y0 = (int)((SY - wh) / 2.0);
	y1 = y0 + wh - 1;
	ystart = max(0, y0);
	yend = min(SY - 1, y1);
	while (ystart < yend)
	{
		my_mlx_pixel_put(&(game->img), x, ystart, color);
		ystart++;
	}
	draw_floor_and_ceil(game, x, y1);
}

//draw
void	render(t_game *game)
{
	int		x;
	int		y;
	dir_t	wdir;
	double	wdist;

	x = 0;
	while (x < SX)
	{
		y = 0;
		while (y < SY)
		{
			my_mlx_pixel_put(&game->img, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < SX)
	{
		wdist = cast_single_ray(x, game, &wdir);
		draw_wall(game, wdist, x, g_wall_colors[wdir]);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}
