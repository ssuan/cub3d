/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:41 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/20 14:05:29 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	empty_line_check(char *line_empty)
{
	int	loop;
	int	line_len;

	loop = 0;
	line_len = ft_strlen(line_empty);
	while (loop < line_len)
	{
		if (is_space(line_empty[loop]) == 0)
			return (0);
		loop++;
	}
	free(line_empty);
	return (1);
}

char	*not_empty_line_load(int fd)
{
	char	*line;
	int		empty_check;

	empty_check = 0;
	while (ft_gnl(fd, &line))
	{
		if (empty_line_check(line) == 1)
			empty_check = 1;
		else
			break ;
	}
	if (empty_check != 1)
		error("Invalid *.cub file - HAS NOT EMPTY SPACE");
	return (line);
}

void	read_cub(char *cub, t_game *game)
{
	int		fd;

	fd = open(cub, O_RDONLY);
	if (fd == -1)
		error("Map not found");
	read_img(fd, game);
	read_rgb(fd, game);
	read_map(fd, game);
}
