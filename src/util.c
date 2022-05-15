/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:46:20 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/15 13:51:33 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "mlx.h"

ft_min
ft_max

#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */ -> 함수

int is_zero(double d)
{
	double eps;

	eps = 1e-06;
	if (fabs(d) < eps)
		return (1);
	else
		return (0);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
	double	dx;
	double	dy;
	
	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int sgn( double d )
{
	if (is_zero(d) == true)
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}
