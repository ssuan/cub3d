/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/17 18:43:06 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// unsigned char???
char	map_get_cell(t_game *game, int x, int y)
{
	if ((x >= 0 && x < game->map.mapX) \
		&& (y >= 0 && y < game->map.mapY))
		return (game->map.map[x][y]);
	else
		return (-1);
}

// 정리 -> 구조체?
int	dx[] = {-1, 1, 0, 0};
int	dy[] = {0, 0, -1, 1};

// game 구조체에 넣기
int	chk[MAPX][MAPY] = {FALSE, };

static void	dfs(t_game *game, int x, int y)
{
	int		i;
	int		nx;
	int		ny;
	char	cell;

	chk[x][y] = TRUE;
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		cell = map_get_cell(game, nx, ny);
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
		else if (cell == '0' && !chk[nx][ny])
			dfs(game, nx, ny);
		i++;
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
			if (game->map.map[x][y] == '0' && !chk[x][y])
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
