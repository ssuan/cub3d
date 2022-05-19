/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:38:49 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 20:01:29 by sunbchoi         ###   ########.fr       */
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
		error("Invalid *.cub file - MAP NOT CLOSE");
	else if (cell != '0' && cell != '1')
		error("Invalid *.cub file - MAP HAS INVALID CHAR");
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
	char	*map_ext;

	if (ac < 2 || ft_strlen(av[1]) == 0)
	{
		error("Please enter the name of the map file you want to use.\n\
			Ex: ./maps/map.cub");
	}
	else if (ac > 2)
	{
		error("Too many argument entered. Please retry it again.\n\
			Ex: ./maps/map.cub");
	}
	map_ext = ft_strrchr(av[1], '.');
	if ((ft_strstr(map_ext, ".cub") == NULL) \
		|| (ft_strlen(map_ext) != ft_strlen(".cub")))
		error("Invalid map extension. Please Enter *.cub");
	return (SUCCESS);
}
