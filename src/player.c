/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:28:30 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 15:06:54 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_move_offset(double th, int key, double amt, double *pdx, double *pdy)
{
	int	sgn;

	if (key == KEY_W || key == KEY_A)
		sgn = 1;
	else
		sgn = -1;
	if (key == KEY_W || key == KEY_S)
	{
		*pdx = sgn * amt * cos(th);
		*pdy = sgn * amt * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		*pdx = amt * cos(th + sgn * M_PI_2);
		*pdy = amt * sin(th + sgn * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int	player_move(player_t *pp, int key, double amt)
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;

	dx = 0;
	dy = 0;
	if (get_move_offset(pp->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return (-1);
	}
	nx = pp->px + dx;
	ny = pp->py + dy;
	if (map_get_cell((int)nx, (int)ny) != 0)
	{
		printf("** bump !\n");
		return (-1);
	}
	pp->px = nx;
	pp->py = ny;
	return (0);
}

void	player_rotate(player_t *pp, double th)
{
	pp->th += th;
	if (pp->th < 0)
		pp->th += _2PI;
	else if (pp->th > _2PI)
		pp->th -= _2PI;
}
