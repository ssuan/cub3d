/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:25:21 by suan              #+#    #+#             */
/*   Updated: 2022/05/17 18:09:00 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_game *game)
{
	int		x;
	int		y;
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
		wdist = cast_single_ray(game, x);
		draw(game, wdist, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}
