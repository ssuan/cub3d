/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:18:56 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/16 21:33:29 by sunbchoi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_rgb(char* line, t_game *game)
{
	int color_temp;
    int *cur;
    char *empty;
    int empty_check;
    int cnt;
    
	// VALID CHECK;
    
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
    
	cnt = 0;
    color_temp = 0;
	/// SAVE
    while (*empty != 0 && (ft_isdigit(*empty) || *empty == ','))
	{
        if (ft_isdigit(*empty))
        {
            color_temp *= 10;
            color_temp += (int)(*empty) - '0';
        }
        else
        {
            if (color_temp >= 0 && color_temp <= 255 && cnt < 2) 
            {
				printf("CNT[%d] : COLOR[%d]\n", color_temp, cnt);
				if (*cur < 0)
					*cur = 0;
				*cur *= 255;
				*cur += color_temp;
				color_temp = 0;
				cnt++;
			}
			else
			{
				perror("Invalid cub file! \n color save fail \n EXIT!");
				exit(1);
			}
        }
        empty++;
    }
	if (color_temp >= 0 && color_temp <= 255) 
    {
		printf("CNT[%d] : COLOR[%d]\n", color_temp, cnt);
		if (*cur < 0)
			*cur = 0;
		*cur *= 255;
		*cur += color_temp;
		color_temp = 0;
		cnt++;
	}
	printf("CUR[%d]\n", *cur);
	printf("F[%d]\n", game->map.floor_color);
	printf("C[%d]\n", game->map.ceil_color);

	if (cnt != 3)
		printf("NOT ENOUGH COLOR");
	return (1);
}

int	read_rgb(int fd, t_game *game)
{
	int	loop;
	char *line;
	
	loop = 0;
	game->map.ceil_color = -1;
    game->map.floor_color = -1;
	while (loop < 2)
	{
		if(!ft_gnl(fd, &line))
		{
			perror("Invalid cub file!\n EXIT!");
			exit(1);
		}
		if(check_rgb(line, game) == 0)
        {    
            perror("Invalid cub file!\n Imege save FAIL!!\n EXIT!");
    	    exit(1);
        }
        loop++;
	}
	if (game->map.ceil_color == -1 || game->map.floor_color == -1)
	{
		perror("Invalid cub file! \n COLOR!! \n EXIT!");
		exit(1);
	}
	return (1);
}
