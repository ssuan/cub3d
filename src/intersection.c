/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:01:06 by suan              #+#    #+#             */
/*   Updated: 2022/05/17 18:32:32 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_sect(t_intersect *sect, double ray)
{
	ft_memset(sect, 0, sizeof(sect));
	sect->xstep = sgn(cos(ray));
	sect->ystep = sgn(sin(ray));
	sect->g = INFINITY;
	sect->f = INFINITY;
	if (sect->xstep == 0)
		sect->xslope = INFINITY;
	else
		sect->xslope = tan(ray);
	if (sect->ystep == 0)
		sect->yslope = INFINITY;
	else
		sect->yslope = 1. / tan(ray);
}

static void	next_pos_init(t_intersect sect, t_player pl, t_pos *next)
{
	if (sect.xstep > 0)
		next->x = floor(pl.px) + 1;
	else if (sect.xstep < 0)
		next->x = ceil(pl.px) - 1;
	else
		next->x = pl.px;
	if (sect.ystep > 0)
		next->y = floor(pl.py) + 1;
	else if (sect.ystep < 0)
		next->y = ceil(pl.py) - 1;
	else
		next->y = pl.py;
}

static void	get_next_map(t_intersect *sect, t_player pl, t_pos next)
{
	if (sect->xstep != 0)
		sect->f = sect->xslope * (next.x - pl.px) + pl.py;
	if (sect->ystep != 0)
		sect->g = sect->yslope * (next.y - pl.py) + pl.px;
	sect->dist_v = l2dist(pl.px, pl.py, next.x, sect->f);
	sect->dist_h = l2dist(pl.px, pl.py, sect->g, next.y);
	if (sect->dist_v < sect->dist_h)
	{
		sect->mapx = (int)(next.x);
		if (sect->xstep != 1)
			sect->mapx -= 1;
		sect->mapy = (int) sect->f;
		sect->hit_side = VERT;
	}
	else
	{
		sect->mapx = (int) sect->g;
		sect->mapy = (int)(next.y);
		if (sect->ystep != 1)
			sect->mapy -= 1;
		sect->hit_side = HORIZ;
	}
}

static int	hit_wall(t_intersect sect, t_pos next, t_game *game)
{
	if (sect.hit_side == VERT)
	{
		if (sect.xstep > 0)
			game->wdir = DIR_W;
		else
			game->wdir = DIR_E;
		game->wpos.x = next.x;
		game->wpos.y = sect.f;
	}
	else
	{
		if (sect.ystep > 0)
			game->wdir = DIR_S;
		else
			game->wdir = DIR_N;
		game->wpos.x = sect.g;
		game->wpos.y = next.y;
	}
	return (TRUE);
}

int	get_wall_intersection(t_game *game, double ray)
{
	t_intersect	sect;
	t_pos		next;
	int			hit;
	char		cell;

	hit = FALSE;
	init_sect(&sect, ray);
	next_pos_init(sect, game->pl, &next);
	while (!hit)
	{
		get_next_map(&sect, game->pl, next);
		cell = map_get_cell(game, sect.mapx, sect.mapy);
		if (cell < 0)
			break ;
		if (cell == '1')
		{
			hit = hit_wall(sect, next, game);
			break ;
		}
		if (sect.hit_side == VERT)
			next.x += sect.xstep;
		else
			next.y += sect.ystep;
	}
	return (hit);
}
