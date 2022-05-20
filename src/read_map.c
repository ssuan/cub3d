/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:39:36 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/20 15:00:01 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player(char *line, int x, int y, t_game *game)
{
	game->pl.px = (float)x + 0.501;
	game->pl.py = (float)y + 0.501;
	if (line[x] == 'N')
	{
		game->wdir = 0;
		game->pl.th = deg2rad(3 * 90);
	}
	else if (line[x] == 'E')
	{
		game->pl.th = deg2rad(0 * 90);
		game->wdir = 1;
	}
	else if (line[x] == 'W')
	{
		game->pl.th = deg2rad(2 * 90);
		game->wdir = 2;
	}
	else if (line[x] == 'S')
	{
		game->pl.th = deg2rad(1 * 90);
		game->wdir = 3;
	}
	line[x] = '0';
}

void	check_player(char *line, t_game *game, int y)
{
	char	key[5];
	int		loop;
	char	*r_val;
	char	*l_val;

	loop = 0;
	ft_memcpy(key, "NEWS", sizeof(char) * 4);
	while (loop < 4)
	{
		l_val = ft_strchr(line, key[loop]);
		r_val = ft_strrchr(line, key[loop]);
		if (r_val != 0 && l_val != 0)
		{
			if (r_val == l_val && game->pl.px == -1.0)
			{	
				set_player(line, (int)(l_val - line), y, game);
			}
			else
				error("Invalid *.cub file - FAIL SET Player");
		}
		loop++;
	}
}

void	save_line_map(char *line, t_game *game, int y)
{
	if (y > 1000)
		error("Invalid *.cub file - map height <= 1000");
	if (game->map.mapx < (int)ft_strlen(line))
		game->map.mapx = (int)ft_strlen(line);
	if (game->map.mapx > 1000)
		error("Invalid *.cub file - map width <= 1000");
	check_player(line, game, y);
	ft_memcpy(game->map.map[y], line, ft_strlen(line));
	game->map.map[y][(ft_strlen(line))] = 0;
	free(line);
}

int	read_map(int fd, t_game *game)
{
	int		loop_y;
	char	*line;

	loop_y = 0;
	game->map.mapx = 0;
	line = not_empty_line_load(fd, 1);
	save_line_map(line, game, loop_y++);
	while (ft_gnl(fd, &line))
	{
		save_line_map(line, game, loop_y);
		loop_y++;
	}
	save_line_map(line, game, loop_y);
	loop_y++;
	game->map.mapy = loop_y;
	return (1);
}
