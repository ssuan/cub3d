/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:25:21 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 20:29:18 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//draw
void	render(t_game *game)
{
	int		x;
	int		y;
	dir_t	wdir;
	double	wdist;
	t_pos	wpos;

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
		wdist = cast_single_ray(x, game, &wdir, &wpos);
		draw(game, wdist, x, wdir, &wpos);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}
