/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 14:44:34 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 빼기
static char	g_map[MAPX][MAPY] = {
	{'1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1'},
	{'1', '1', ' ', '1', '1'}
};

//chk
// unsigned char???
char	map_get_cell( int x, int y )
{
	if ((x >= 0 && x < MAPX) \
		&& (y >= 0 && y < MAPY))
		return (g_map[x][y]);
	else
		return (-1);
}

// 정리 -> 구조체?
int	dx[] = {-1, 1, 0, 0};
int	dy[] = {0, 0, -1, 1};

// game 구조체에 넣기
bool	chk[MAPX][MAPY] = {false, };

void	dfs(int x, int y)
{
	int		i;
	int		nx;
	int		ny;
	char	cell;

	chk[x][y] = true;
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		cell = map_get_cell(nx, ny);
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
			dfs(nx, ny);
		i++;
	}
}

void	map_check(void)
{
	int	x;
	int	y;

	x = 0;
	while (x < MAPX)
	{
		y = 0;
		while (y < MAPY)
		{
			if (g_map[x][y] == '0' && !chk[x][y])
			{
				dfs(x, y);
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
		return (0);
	}
	return (1);
}
