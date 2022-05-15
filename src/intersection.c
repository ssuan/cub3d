/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:01:06 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 17:17:55 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sect(t_sector *sect, double ray)
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

void	next_pos_init(player_t pl, t_pos *next, t_sector sect)
{
	if (sect.xstep > 0)
		next->pos_x = floor(pl.px) + 1;
	else if (sect.xstep < 0)
		next->pos_x = ceil(pl.px) - 1;
	else
		next->pos_x = pl.px;
	if (sect.ystep > 0)
		next->pos_y = floor(pl.py) + 1;
	else if (sect.ystep < 0)
		next->pos_y = ceil(pl.py) - 1;
	else
		next->pos_y = pl.py;
}

void	get_next_map(t_sector *sect, t_pos next, player_t pl)
{
	if (sect->xstep != 0)
		sect->f = sect->xslope * (next.pos_x - pl.px) + pl.py;
	if (sect->ystep != 0)
		sect->g = sect->yslope * (next.pos_y - pl.py) + pl.px;
	sect->dist_v = l2dist(pl.px, pl.py, next.pos_x, sect->f);
	sect->dist_h = l2dist(pl.px, pl.py, sect->g, next.pos_y);
	if (sect->dist_v < sect->dist_h)
	{
		sect->mapx = (sect->xstep == 1) ? (int)(next.pos_x) : (int)(next.pos_x) - 1 ;
		sect->mapy = (int) sect->f;
		sect->hit_side = VERT;
		printf(" V(%d, %.2f) ->", sect->mapx, sect->f);
	}
	else
	{
		sect->mapx = (int) sect->g;
		sect->mapy = (sect->ystep == 1) ? (int)(next.pos_y) : (int)(next.pos_y) - 1 ;
		sect->hit_side = HORIZ;
		printf(" H(%.2f, %d) ->", sect->g, sect->mapy);
	}
}

static bool	hit_wall(t_sector sect, t_pos next, dir_t *wdir, t_pos *wpos)
{
	if (sect.hit_side == VERT)
	{
		*wdir = (sect.xstep > 0) ? DIR_W : DIR_E;
		wpos->pos_x = next.pos_x;
		wpos->pos_y = sect.f;
	}
	else
	{
		*wdir = (sect.ystep > 0) ? DIR_S : DIR_N;
		wpos->pos_x = sect.g;
		wpos->pos_y = next.pos_y;
	}
	printf(" hit wall!\n");
	return (true);
}

bool	get_wall_intersection(double ray, player_t pl, dir_t *wdir, t_pos *wpos)
{
	t_sector	sect;
	t_pos		next;
	bool		hit;
	int			cell;

	hit = false;
	init_sect(&sect, ray);
	next_pos_init(pl, &next, sect);
	while (!hit)
	{
		get_next_map(&sect, next, pl);
		cell = map_get_cell(sect.mapx, sect.mapy);
		if (cell < 0)
			break ;
		if (cell == 1)
		{
			hit = hit_wall(sect, next, wdir, wpos);
			break ;
		}
		if (sect.hit_side == VERT)
			next.pos_x += sect.xstep;
		else
			next.pos_y += sect.ystep;
	}
	return (hit);
}
