/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:39:36 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/19 14:37:23 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player(char *line, int x, int y, t_game *game)
{
	game->pl.px = (float)x + 0.5;
	game->pl.py = (float)y + 0.5;
	if (line[x] == 'W')
		game->pl.th = deg2rad(0 * 90);
	else if (line[x] == 'S')
		game->pl.th = deg2rad(1 * 90);
	else if (line[x] == 'E')
		game->pl.th = deg2rad(2 * 90);
	else if (line[x] == 'N')
		game->pl.th = deg2rad(3 * 90);
	line[x] = '0';
}


// # define DIR_N 0
// # define DIR_E 1
// # define DIR_W 2
// # define DIR_S 3 

void	check_player(char *line, t_game *game, int y)
{
	char	key[5];
	int		loop;
	int		pos;
	char	*r_val;
	char	*l_val;

	loop = 0;
	ft_memcpy(key, "SENW", sizeof(char) * 4);
	while (loop < 4)
	{
		l_val = ft_strchr(line, key[loop]);
		r_val = ft_strrchr(line, key[loop]);
		if (r_val != 0 && l_val != 0)
		{
			if (r_val == l_val && game->pl.px == -1.0)
			{	
				set_player(line, (int)(l_val - line), y, game);
				game->wdir = loop;
			}
			else
				error("Invalid *.cub file - FAIL SET Player");
		}
		loop++;
	}
}

void	map_reverse(t_game *game)
{
	int temp;
	double dtemp;
	int lpy;
	int lpx;
	char save_map[1000][1000];

	lpy = 0;
	while (lpy < 1000)
	{
		ft_memcpy(save_map[lpy], game->map.map[lpy] , sizeof(char) * 1000);
		lpy++;
	}
	lpy = 0;
	while (lpy < 1000)
		ft_memset(game->map.map[lpy++], 0, sizeof(char) * 1000);
	lpy = 0;
	while (lpy < 1000)
	{
		lpx = 0;
		while (lpx < 1000)
		{
			game->map.map[lpx][lpy] = save_map[lpy][lpx];
			lpx++;
		}
		lpy++;
	}
	temp = game->map.mapY;
	game->map.mapY = game->map.mapX;
	game->map.mapX = temp;

	dtemp = game->pl.py;
	game->pl.py = game->pl.px;
	game->pl.px = dtemp;
}

void	save_line_map(char *line, t_game *game, int y)
{
	if (y > 1000)
		error("Invalid *.cub file - map height <= 1000");
	if (game->map.mapX < ft_strlen(line))
		game->map.mapX = ft_strlen(line);
	if (game->map.mapX > 1000)
		error("Invalid *.cub file - map width <= 1000");
	check_player(line, game, y);
	ft_memcpy(game->map.map[y], line, ft_strlen(line));
	game->map.map[y][(ft_strlen(line))] = 0;
	free(line);
}

int	read_map(int fd, t_game *game)
{
	int		loop_y;
	char	key;
	char	*line;

	loop_y = 0;
	game->map.mapX = 0;
	line = not_empty_line_load(fd);
	save_line_map(line, game, loop_y++);
	printf("[%s]\n", game->map.map[0]);
	while (ft_gnl(fd, &line))
	{
		save_line_map(line, game, loop_y);
		printf("[%s]\n", game->map.map[loop_y]);
		loop_y++;
	}
	save_line_map(line, game, loop_y);
	printf("[%s]\n", game->map.map[loop_y]);
	loop_y++;
	game->map.mapY = loop_y;
	
	
	int loop_x;
	loop_x = 0;
	map_reverse(game);
	printf("\n\nREV\n\n", game->map.map[loop_y]);
	while (loop_x < 1000)
	{
		loop_y = 0;
		while (loop_y < 1000)
		{
			if (game->map.map[loop_x][loop_y] != 0)
				printf("[%c]", game->map.map[loop_x][loop_y]);
			loop_y++;
		}
		loop_x++;
		printf("\n");
	}
	
	return (1);
}
