/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:39:36 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/16 21:39:32 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	read_map(int fd, t_game *game)
{
	int		loop_x;
	int		loop_y;
	char	key;
    char    *line;

    loop_x = 0;
	loop_y = 0;
    game->map.max_lenX = 0;
    game->map.max_lenY = 0;
	while (ft_gnl(fd, &line))
	{
        ft_memcpy(game->map.map[loop_x], line, ft_strlen(line));
        if (game->map.max_lenX < ft_strlen(line))
            game->map.max_lenX = ft_strlen(line);
        game->map.map[loop_x][(ft_strlen(line))] = 0;
        printf("[%s]\n", game->map.map[loop_x]);
        loop_y++;
	}
    ft_memcpy(game->map.map[loop_x], line, ft_strlen(line));
    if (game->map.max_lenX < ft_strlen(line))
        game->map.max_lenX = ft_strlen(line);
    game->map.map[loop_x][(ft_strlen(line))] = 0;
    printf("[%s]\n", game->map.map[loop_x]);
    game->map.max_lenY = loop_y;
    return (1);
}