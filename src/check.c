/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/17 16:50:12 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 빼기
// static char	g_map[MAPX][MAPY] = {
// 			동
// 	{'1', '1', '1', '1', '1'},
// 	{'1', '0', '0', '1', '1'},
// 	{'1', '0', '0', '0', '1'},
// 북	 {'1', '0', '0', '0', '1'},	남
// 	{'1', '0', '1', '1', '1'},
// 	{'1', '1', ' ', '1', '1'}
// };			?서 0

//chk
// unsigned char???
char	map_get_cell(t_game *game, int x, int y)
{
	if ((x >= 0 && x < game->map.max_lenX) \
		&& (y >= 0 && y < game->map.max_lenY))
		return (game->map.map[x][y]);
	else
		return (-1);
}

// 정리 -> 구조체?
int	dx[] = {-1, 1, 0, 0};
int	dy[] = {0, 0, -1, 1};

// game 구조체에 넣기
bool	chk[MAPX][MAPY] = {false, };

void	dfs(t_game *game, int x, int y)
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
	while (x < MAPX)
	{
		y = 0;
		while (y < MAPY)
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
	// if (ac != 4)
	// {
	// 	fprintf(stderr, "usage: %s x y th(deg)\n", av[0]);
	// 	return (0);
	// }
	
	char	*map_ext;

	if (ac < 2 || ft_strlen(av[1]) == 0)
	{
		perror("Please enter the name of the map file you want to use.\n\
			Ex: ./maps/map.cub");
	}
	else if (ac > 2)
	{
		perror("Too many argument entered. Please retry it again.\n\
			Ex: ./maps/map.cub");
	}
	map_ext = ft_strrchr(av[1], '.');
	if ((ft_strstr(map_ext, ".cub") == NULL) \
		|| (ft_strlen(map_ext) != ft_strlen(".cub")))
		perror("Invalid map extension. Please Enter *.cub");
	return (1);
}
