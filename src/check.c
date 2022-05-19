/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 18:17:40 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 빼기
static char	g_map[MAPY][MAPX] = {
	{'1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '1'},
	{'1', '1', '1', '1', '1'}
};

/*
e: blue 180
n: red 270
s: grey 90
w: wood 0
*/

// unsigned char???
char	map_get_cell(t_game *game, int x, int y)
{
	if ((x >= 0 && x < MAPX) \
		&& (y >= 0 && y < MAPY))
		return (g_map[y][x]);
	else
		return (-1);
}

// game 구조체에 넣기
int	chk[MAPY][MAPX] = {FALSE, };

static void dfs(t_game *game, int x, int y)
{
    char    cell;

    if (chk[y][x])
        return ;
    chk[y][x] = TRUE;
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
	while (x < MAPX)
	{
		y = 0;
		while (y < MAPY)
		{
			if (g_map[y][x] == '0' && !chk[y][x])
			{
				dfs(game, x, y);
			}
			y++;
		}
		x++;
	}

	y = 0;
	while (y < MAPY)
	{
		x = 0;
		while (x < MAPX)
		{
			printf("%c", g_map[y][x]);
			x++;
		}
		y++;
		printf("\n");
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
