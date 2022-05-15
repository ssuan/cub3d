/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:32:03 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 15:00:34 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//ray
double	cast_single_ray(int x, player_t pl, dir_t *wdir)
{
	double	ray;
	double	wx;
	double	wy;
	double	wdist;

	ray = (pl.th + (FOV_H / 2.0)) - (x * (FOV_H / (SX - 1.)));
	if (get_wall_intersection(ray, pl.px, pl.py, wdir, &wx, &wy) == false)
		return (INFINITY);
	wdist = l2dist(pl.px, pl.py, wx, wy);
	wdist *= cos(pl.th - ray);
	return (wdist);
}
