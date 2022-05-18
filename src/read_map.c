/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:39:36 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/18 23:06:07 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	save_line_map(char *line, t_game *game, int y)
{
	if (y > 1000)
		error("Invalid *.cub file - map height <= 1000");
	if (game->map.mapX < ft_strlen(line))
		game->map.mapX = ft_strlen(line);
	if (game->map.mapX > 1000)
		error("Invalid *.cub file - map width <= 1000");
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
	game->map.mapY = loop_y;
	return (1);
}
