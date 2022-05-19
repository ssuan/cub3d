/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:27:37 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 17:23:01 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		y = y1;
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
// 노션에서 tx, ty 참고
// 텍스처 부분은 https://stdbc.tistory.com/62 참고
// game에 wdir, wpos 넣어서 매개변수 줄이기
static void	draw_wall(t_game *game, int wh, int x, int y0)
{
	int		y;
	int		yend;
	double	txratio;
	t_pos	tpos;
	int		color;

	y = max(0, y0);
	yend = min(SY - 1, y0 + wh - 1);
	txratio = game->wpos.x - floor(game->wpos.x);
	if (game->wdir == DIR_W || game->wdir == DIR_E)
		txratio = game->wpos.y - floor(game->wpos.y);
	tpos.x = txratio * game->wall[game->wdir].w;
	while (y <= yend)
	{
		tpos.y = (double)(y - y0) * game->wall[game->wdir].h / wh;
		color = game->wall[game->wdir].data[game->wall[game->wdir].size_l \
			 / (game->wall[game->wdir].bpp / 8) * (int)tpos.y + (int)tpos.x];
		my_mlx_pixel_put(&(game->img), x, y, color);
		y++;
	}
}

void	draw(t_game *game, double wdist, int x)
{
	int		wh;
	int		y0;
	int		y1;

	wh = get_wall_height(game, wdist);
	y0 = (int)((SY - wh) / 2.0);
	y1 = y0 + wh - 1;
	draw_wall(game, wh, x, y0);
	draw_floor_and_ceil(game, x, y1);
}
