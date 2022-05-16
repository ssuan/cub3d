/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:18:56 by sunbchoi@st       #+#    #+#             */
/*   Updated: 2022/05/16 19:30:50 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int save_xpm(char* line, t_game *game, int *check, int dir)
{
	char *empty;
	int empty_check;
	char *xpm;
	int w;
	int h;

	empty = &line[2];
	while (*empty == ' ')
	{
		empty_check = 1;
		empty++;
	}
	if (empty_check == 1 && *empty == '.')
	{
		xpm = ft_strdup(empty);
		printf("XPM[%s]\n", xpm);
		game->map.xpm[dir] = mlx_xpm_file_to_image(game->mlx, xpm, &w, &h);
		check[dir] = 1;
	}
	// if (game->map.xpm[dir] == NULL)
	// {
	// 	perror("Invalid cub file! \n xpm save fail \n EXIT!");
	// 	return (0);
	// }
	free(xpm);
	return (1);
}

int check_img(char* line, t_game *game, int *check)
{
	char dir[3];
	int dir_num;

	dir_num = -1;
	ft_memset(dir, 0 , sizeof(char) * 3);
	ft_memcpy(dir, line, 2);
	printf("DIR[%s]\n", dir);
	if (ft_strnstr(dir, "NO", 2))
		dir_num = 0;
	else if (ft_strnstr(dir, "SO", 2))
		dir_num = 1;
	else if (ft_strnstr(dir, "WE", 2))
		dir_num = 2;
	else if (ft_strnstr(dir, "EA", 2))
		dir_num = 3;
	else
		return (0);
	if (save_xpm(line, game, check, dir_num))
		return (1);
	else
		return (0);
}

int	read_img(int fd, t_game *game)
{
	int ck[4];
	int	loop;
	char *line;
	
	ft_memset(ck, 0, sizeof(int) * 4);
	loop = 0;
	while (loop < 4)
	{
		if(!ft_gnl(fd, &line))
		{
			perror("Invalid cub file!\n EXIT!");
			exit(1);
		}
		printf("LINE=[%s]\n", line);
		if(check_img(line, game, ck) == 0)
        {    
            perror("Invalid cub file!\n Imege save FAIL!!\n EXIT!");
    	    exit(1);
        }
        loop++;
	}
	if (ck[0] != 1 || ck[1] != 1 \
	|| ck[2] != 1 || ck[3] != 1)
	{
		perror("Invalid cub file!\n EXIT!");
		exit(1);
	}
	return (1);
}
