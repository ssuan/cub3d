/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:01:06 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 22:05:37 by sunbchoi@st      ###   ########.fr       */
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

void	get_next_map(t_sector *sect, t_pos next, player_t pl)
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
		printf(" V(%d, %.2f) ->", sect->mapx, sect->f);
	}
	else
	{
		sect->mapx = (int) sect->g;
		sect->mapy = (int)(next.y);
		if (sect->ystep != 1)
			sect->mapy -= 1;
		sect->hit_side = HORIZ;
		printf(" H(%.2f, %d) ->", sect->g, sect->mapy);
	}
}

static bool	hit_wall(t_sector sect, t_pos next, dir_t *wdir, t_pos *wpos)
{
	if (sect.hit_side == VERT)
	{
		if (sect.xstep > 0)
			*wdir = DIR_W;
		else
			*wdir = DIR_E;
		wpos->x = next.x;
		wpos->y = sect.f;
	}
	else
	{
		if (sect.ystep > 0)
			*wdir = DIR_S;
		else
			*wdir = DIR_N;
		wpos->x = sect.g;
		wpos->y = next.y;
	}
	printf(" hit wall!\n");
	return (true);
}

bool	get_wall_intersection(double ray, player_t pl, dir_t *wdir, t_pos *wpos)
{
	t_sector	sect;
	t_pos		next;
	bool		hit;
	char		cell;

	hit = false;
	init_sect(&sect, ray);
	next_pos_init(pl, &next, sect);
	while (!hit)
	{
		get_next_map(&sect, next, pl);
		cell = map_get_cell(sect.mapx, sect.mapy);
		if (cell < 0)
			break ;
		if (cell == '1')
		{
			hit = hit_wall(sect, next, wdir, wpos);
			break ;
		}
		if (sect.hit_side == VERT)
			next.x += sect.xstep;
		else
			next.y += sect.ystep;
	}
	return (hit);
}
