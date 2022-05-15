/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:32:03 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 16:15:00 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//ray
double	cast_single_ray(int x, t_game *game, dir_t *wdir)
{
	double	ray;
	t_pos	pos;
	double	wdist;

	ray = (game->pl.th + (game->fov_h / 2.0)) - (x * game->per_angle);
	if (!(get_wall_intersection(ray, game->pl, wdir, &pos)))
		return (INFINITY);
	wdist = l2dist(game->pl.px, game->pl.py, pos.pos_x, pos.pos_y);
	wdist *= cos(game->pl.th - ray);
	return (wdist);
}
