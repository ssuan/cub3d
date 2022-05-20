/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:28:30 by suan              #+#    #+#             */
/*   Updated: 2022/05/20 14:58:46 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_move_offset(double th, int key, double amt, t_pos *dpos)
{
	int	sgn;

	if (key == KEY_W || key == KEY_D)
		sgn = 1;
	else
		sgn = -1;
	if (key == KEY_W || key == KEY_S)
	{
		dpos->x = sgn * amt * cos(th);
		dpos->y = sgn * amt * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		dpos->x = amt * cos(th + sgn * M_PI_2);
		dpos->y = amt * sin(th + sgn * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int	player_move(t_game *game, int key, double amt)
{
	t_pos	dpos;
	double	nx;
	double	ny;

	dpos.x = 0;
	dpos.y = 0;
	if (get_move_offset(game->pl.th, key, amt, &dpos) < 0)
		return (-1);
	nx = game->pl.px + dpos.x;
	ny = game->pl.py + dpos.y;
	if (map_get_cell(game, (int)nx, (int)ny) != '0')
	{
		ft_putstr_fd("** bump !\n", 1);
		return (-1);
	}
	game->pl.px = nx;
	game->pl.py = ny;
	return (0);
}

void	player_rotate(t_player *pl, double th)
{
	pl->th -= th;
	if (pl->th < 0)
		pl->th += _2PI;
	else if (pl->th > _2PI)
		pl->th -= _2PI;
}
