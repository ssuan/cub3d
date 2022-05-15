/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:46:20 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/15 14:32:11 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "mlx.h"

int  ft_min(int val1, int val2)
{
	if (val1 < val2)
		return (val1);
	else
		return (val2);
}

int  ft_max(int val1, int val2)
{
	if (val1 > val2)
		return (val1);
	else
		return (val2);
}

// double deg2rad(double degree)
// {
// 	return (((degree) * M_PI / 180.0));
// }

// double rad2deg(double radian)
// {
// 	return ((radian) * 180.0 / M_PI);
// }

// int is_zero(double d)
// {
// 	double eps;

// 	eps = 1e-06;
// 	if (fabs(d) < eps)
// 		return (1);
// 	else
// 		return (0);
// }

// double l2dist( double x0, double y0, double x1, double y1 )
// {
// 	double	dx;
// 	double	dy;
	
// 	dx = x0 - x1;
// 	dy = y0 - y1;
// 	return (sqrt(dx * dx + dy * dy));
// }

// int sgn( double d )
// {
// 	if (is_zero(d) == TRUE)
// 		return (0);
// 	else if (d > 0)
// 		return (1);
// 	else
// 		return (-1);
// }
