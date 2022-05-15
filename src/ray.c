/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:32:03 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 15:25:08 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//ray
double	cast_single_ray(int x, t_game *game, dir_t *wdir)
{
	double	ray;
	double	wx;
	double	wy;
	double	wdist;

	ray = (game->pl.th + (game->fov_h / 2.0)) - (x * game->per_angle);
	if (!(get_wall_intersection(ray, game->pl.px, game->pl.py, wdir, &wx, &wy)))
		return (INFINITY);
	wdist = l2dist(game->pl.px, game->pl.py, wx, wy);
	wdist *= cos(game->pl.th - ray);
	return (wdist);
}
