/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:27:37 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 20:27:38 by suan             ###   ########.fr       */
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
static void	draw_wall(t_game *game, int x, dir_t wdir, t_pos *wpos, int wh, int y0, int y1)
{
	int		y;
	int		yend;
	double	txratio;
	t_pos	tpos;
	int		color;

	y = max(0, y0);
	yend = min(SY - 1, y1);
	txratio = wpos->x - floor(wpos->x);
	if (wdir == DIR_W || wdir == DIR_E)
		txratio = wpos->y - floor(wpos->y);
	tpos.x = txratio * game->wall[wdir].w;
	while (y <= yend)
	{
		tpos.y = (double)(y - y0) *game->wall[wdir].h / wh;
		color = game->wall[wdir].data[game->wall[wdir].size_l \
			 / (game->wall[wdir].bpp / 8) * (int)tpos.y + (int)tpos.x];
		my_mlx_pixel_put(&(game->img), x, y, color);
		y++;
	}
	draw_floor_and_ceil(game, x, y1);
}

void	draw(t_game *game, double wdist, int x, dir_t wdir, t_pos *wpos)
{
	int		wh;
	int		y0;
	int		y1;

	wh = get_wall_height(game, wdist);
	y0 = (int)((SY - wh) / 2.0);
	y1 = y0 + wh - 1;
	draw_wall(game, x, wdir, wpos, wh, y0, y1);
	draw_floor_and_ceil(game, x, y1);
}
