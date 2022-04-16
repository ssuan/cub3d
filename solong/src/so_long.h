/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:32:29 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 18:26:07 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include "./../libft/libft.h"

# define ITEM_KEY "10CPE"
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53
# define SUCCESS 1
# define FAILURE 0

typedef struct s_img
{
	void	*w;
	void	*g;
	void	*e;
	void	*c;
	void	*p;
}	t_img;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_game
{
	int		point_cnt;
	int		item_cnt;
	int		exit_cnt;
	int		step_cnt;
	t_pos	pos;
}	t_game;

typedef struct s_map
{
	char	**mtx;
	int		x_len;
	int		y_len;
	t_game	g_data;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	m_data;
}	t_data;

int		error(char *msg);
void	initialize_data(char *argv[], t_data *data);
int		check_area(t_data *data);
int		check_map(t_data *data);
int		key_press(int keycode, t_data *data);
void	print_draw_map(t_data *data);
void	print_shall_map(char **map, t_data *data);
int		close_map(void);
#endif