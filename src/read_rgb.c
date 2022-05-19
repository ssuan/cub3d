/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:18:56 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/19 20:02:36 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_value_rgb(int *cur, int *color, int *cnt)
{
	if (*color >= 0 && *color <= 255 && (*cnt) < 3)
	{
		if (*cur < 0)
			*cur = 0;
		*cur *= 255;
		*cur += *color;
		*color = 0;
		(*cnt)++;
	}
	else
		error("Invalid *.cub file - FAIL SAVE!! RGB");
}

void	save_rgb(char *line, int *cur, t_game *game)
{
	int	cnt;
	int	value;

	cnt = 0;
	value = 0;
	while (*line != 0 && (ft_isdigit(*line) || *line == ','))
	{
		if (ft_isdigit(*line))
		{
			value *= 10;
			value += (int)(*line) - '0';
		}
		else
			set_value_rgb(cur, &value, &cnt);
		line++;
	}
	set_value_rgb(cur, &value, &cnt);
	if (cnt != 3)
		error("Invalid *.cub file - NOT ENOUGH COLOR");
}

int	check_rgb(char *line, t_game *game)
{
	int		*cur;
	char	*empty;
	int		empty_check;

	if (line[0] == 'F')
		cur = &(game->map.floor_color);
	else if (line[0] == 'C')
		cur = &(game->map.ceil_color);
	empty = &line[1];
	while (*empty == ' ')
	{
		empty_check = 1;
		empty++;
	}
	if (empty_check != 1)
		error("Invalid *.cub file - NOT ENOUGH SPACE COLOR");
	save_rgb(empty, cur, game);
	free(line);
	return (1);
}

int	read_rgb(int fd, t_game *game)
{
	char	*line;
	int		empty_check;

	game->map.ceil_color = -1;
	game->map.floor_color = -1;
	line = not_empty_line_load(fd);
	if (check_rgb(line, game) == 0)
		error("Invalid *.cub file - FAIL SAVE RGB");
	if (!ft_gnl(fd, &line))
		error("Invalid *.cub file - FAIL READ");
	if (check_rgb(line, game) == 0)
		error("Invalid *.cub file - FAIL SAVE RGB");
	if (game->map.ceil_color == -1 || game->map.floor_color == -1)
		error("Invalid *.cub file - NOT SAVING ALL COLOR");
	return (1);
}
