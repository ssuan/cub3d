/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:46:20 by sunbchoi@st       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/15 14:32:11 by sunbchoi@st      ###   ########.fr       */
=======
/*   Updated: 2022/05/15 14:45:20 by suan             ###   ########.fr       */
>>>>>>> 5c8f48d2e2d58342ed6b84db72d377ec713962d6
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

<<<<<<< HEAD
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
=======
//math? util?
int	is_zero(double d)
{
	double	eps;

	eps = 1e-06;
	if (fabs(d) < eps)
		return (1);
	else
		return (0);
}

//math? util?
int	sgn(double d)
{
	if (is_zero(d) == true)
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}

//math
double	l2dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

double	deg2rad(double degree)
{
	return (((degree) * M_PI / 180.0));
}

double	rad2deg(double radian)
{
	return ((radian) * 180.0 / M_PI);
}

// #define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
// #define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */ -> 함수
>>>>>>> 5c8f48d2e2d58342ed6b84db72d377ec713962d6
