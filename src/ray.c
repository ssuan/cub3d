/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:32:03 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 21:07:44 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	cast_single_ray(t_game *game, int x)
{
	double	ray;
	double	wdist;

	ray = (game->pl.th + (game->fov_h / 2.0)) - (x * game->per_angle);
	if (get_wall_intersection(game, ray) == FALSE)
		return (INFINITY);
	wdist = l2dist(game->pl.px, game->pl.py, game->wpos.x, game->wpos.y);
	wdist *= cos(game->pl.th - ray);
	return (wdist);
}
