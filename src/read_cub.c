/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:41 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/16 21:34:25 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		empty_line_check(int fd)
{
	int loop;
	char *line_empty;

	ft_gnl(fd, &line_empty);	
	free(line_empty);
	return (0);
}

void	read_cub(char *cub, t_game *game)
{
	int		fd;
	int		y_len;

	fd = open(cub, O_RDONLY);
	if (fd == -1)
		perror("Map not found");
	read_img(fd, game);
	empty_line_check(fd);
	read_rgb(fd, game);
	empty_line_check(fd);
	read_map(fd, game);
}