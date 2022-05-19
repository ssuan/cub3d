/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:18:56 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/19 20:02:07 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	save_xpm(char *line, t_game *game, int *check, int dir)
{
	char	*empty;
	char	*xpm;
	int		empty_check;
	int		w;
	int		h;

	empty = &line[2];
	while (*empty == ' ')
	{
		empty_check = 1;
		empty++;
	}
	if (empty_check == 1 && *empty == '.')
	{
		xpm = ft_strdup(empty);
		load_image(game, &game->wall[dir], xpm);
		check[dir] = 1;
	}
	free(xpm);
	return (1);
}

int	check_img(char *line, t_game *game, int *check)
{
	char	dir[3];
	int		dir_num;

	dir_num = -1;
	ft_memset(dir, 0, sizeof(char) * 3);
	ft_memcpy(dir, line, 2);
	if (ft_strnstr(dir, "NO", 2))
		dir_num = 0;
	else if (ft_strnstr(dir, "EA", 2))
		dir_num = 1;
	else if (ft_strnstr(dir, "WE", 2))
		dir_num = 2;
	else if (ft_strnstr(dir, "SO", 2))
		dir_num = 3;
	else
		return (0);
	if (save_xpm(line, game, check, dir_num))
		free(line);
	return (1);
}

int	read_img(int fd, t_game *game)
{
	int		ck[4];
	int		loop;
	char	*line;

	ft_memset(ck, 0, sizeof(int) * 4);
	loop = 0;
	while (loop < 4)
	{
		if ((ft_gnl(fd, &line)) == 0)
			error("Invalid *.cub file - FAIL READ");
		if ((check_img(line, game, ck) == 0))
			error("Invalid *.cub file - FAIL SAVE IMAGE");
		loop++;
	}
	if (ck[0] != 1 || ck[1] != 1 \
	|| ck[2] != 1 || ck[3] != 1)
		error("Invalid *.cub file - NOT SAVING ALL XPM");
	return (1);
}
