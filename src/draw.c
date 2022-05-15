/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:27:37 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 14:42:32 by suan             ###   ########.fr       */
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

static int	get_wall_height( double dist )
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(FOV_V / 2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}

//wall
static void	draw_wall( t_data img, double wdist, int x, int color )
{
	int	wh;
	int	y0;
	int	y1;
	int	ystart;
	int	yend;

	wh = get_wall_height(wdist);
	y0 = (int)((SY - wh) / 2.0);
	y1 = y0 + wh - 1;
	ystart = max(0, y0);
	yend = min(SY - 1, y1);
	while (ystart < yend)
	{
		my_mlx_pixel_put(&img, x, ystart, color);
		ystart++;
	}
}

//draw
void	render( t_game *game )
{
	int		loop;
	int		loop2;
	dir_t	wdir;
	double	wdist;

	loop = 0;
	loop2 = 0;
	while (loop < SX)
	{
		while (loop2 < SY)
		{
			my_mlx_pixel_put(&game->img, loop, loop2, 0xFFFFFF);
			loop2++;
		}
		loop2 = 0;
		loop++;
	}
	loop = 0;
	while (loop < SX)
	{
		wdist = cast_single_ray(loop, game->pl, &wdir);
		draw_wall(game->img, wdist, loop, g_wall_colors[wdir]);
		loop++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}
