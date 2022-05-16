/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:28:30 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 14:24:37 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_move_offset(double th, int key, double amt, t_pos *dpos)
{
	int	sgn;

	if (key == KEY_W || key == KEY_A)
		sgn = 1;
	else
		sgn = -1;
	if (key == KEY_W || key == KEY_S)
	{
		dpos->pos_x = sgn * amt * cos(th);
		dpos->pos_y = sgn * amt * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		dpos->pos_x = amt * cos(th + sgn * M_PI_2);
		dpos->pos_y = amt * sin(th + sgn * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int	player_move(player_t *pp, int key, double amt)
{
	t_pos	dpos;
	double	nx;
	double	ny;

	dpos.pos_x = 0;
	dpos.pos_y = 0;
	if (get_move_offset(pp->th, key, amt, &dpos) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return (-1);
	}
	nx = pp->px + dpos.pos_x;
	ny = pp->py + dpos.pos_y;
	if (map_get_cell((int)nx, (int)ny) != '0')
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
