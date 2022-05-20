/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:41 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/20 14:54:08 by sunbchoi         ###   ########.fr       */
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

char	*not_empty_line_load(int fd, int check)
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
	if (check == 1 && empty_check != 1)
		error("Invalid *.cub file - HAS NOT EMPTY SPACE");
	return (line);
}

int	read_something(char *line)
{
	char	syntex[5];
	char	*check;
	int		space_pos;

	ft_memset(syntex, 0, sizeof(char) * 4);
	ft_memcpy(syntex, line, 3);
	check = ft_strchr(syntex, ' ');
	space_pos = (int)(check - syntex);
	if (space_pos == 2)
		return (1);
	else if (space_pos == 1)
		return (2);
	else
		error("Invalid *.cub file - Unknown input");
	return (0);
}

void	read_cub(char *cub, t_game *game)
{
	int		fd;
	int		read_case;
	char	*line;

	fd = open(cub, O_RDONLY);
	if (fd == -1)
		error("Map not found");
	line = not_empty_line_load(fd, 0);
	if (line == NULL)
		error("Invalid *.cub file - FAIL READ");
	read_case = read_something(line);
	if (read_case == 1)
		read_img(fd, game, line);
	else if (read_case == 2)
		read_rgb(fd, game, line);
	line = not_empty_line_load(fd, 1);
	if (line == NULL)
		error("Invalid *.cub file - FAIL READ");
	read_case = read_something(line);
	if (read_case == 1)
		read_img(fd, game, line);
	else if (read_case == 2)
		read_rgb(fd, game, line);
	read_map(fd, game);
}
