/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 19:13:13 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
e: blue 180
n: red 270
s: grey 90
w: wood 0
*/

char	map_get_cell(t_game *game, int x, int y)
{
	if ((x >= 0 && x < game->map.mapX) \
		&& (y >= 0 && y < game->map.mapY))
		return (game->map.map[y][x]);
	else
		return (-1);
}

static void	dfs(t_game *game, int x, int y)
{
	char	cell;

	if (game->map.chk[y][x])
		return ;
	game->map.chk[y][x] = TRUE;
	cell = map_get_cell(game, x, y);
	if (cell == -1)
	{
		fprintf(stderr, "not closed\n");
		exit(1);
	}
	else if (cell != '0' && cell != '1')
	{
		fprintf(stderr, "invalid char\n");
		exit(1);
	}
	else if (cell == '0')
	{
		dfs(game, x + 1, y);
		dfs(game, x - 1, y);
		dfs(game, x, y + 1);
		dfs(game, x, y - 1);
	}
}

void	map_check(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.mapX)
	{
		y = 0;
		while (y < game->map.mapY)
		{
			if (game->map.map[y][x] == '0' && !game->map.chk[y][x])
			{
				dfs(game, x, y);
			}
			y++;
		}
		x++;
	}
}

int	input_check(int ac, char **av)
{
	if (ac != 4)
	{
		fprintf(stderr, "usage: %s x y th(deg)\n", av[0]);
		return (FAIL);
	}
	return (SUCCESS);
}
