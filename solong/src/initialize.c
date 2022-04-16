/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:10:49 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 17:17:14 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(char *argv[], t_data *data)
{
	int		fd;
	int		loop;
	char	*line;
	int		y_len;

	data->m_data.y_len = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error("Map not found");
	while (ft_gnl(fd, &line))
	{
		data->m_data.y_len++;
		free(line);
	}
	fd = open(argv[1], O_RDONLY);
	y_len = data->m_data.y_len;
	data->m_data.mtx = (char **)ft_calloc(sizeof(char *), y_len + 1);
	loop = 0;
	while (ft_gnl(fd, &line))
	{
		data->m_data.x_len = ft_strlen(line);
		data->m_data.mtx[loop++] = line;
	}
	free(line);
	close(fd);
}

void	read_img(t_data *data)
{
	int		w;
	int		h;
	void	*mlx;

	mlx = data->mlx;
	data->img.w = mlx_xpm_file_to_image(mlx, "./img/Wall.xpm", &w, &h);
	if (data->img.w == NULL)
		error("Invalid image file : Wall");
	data->img.g = mlx_xpm_file_to_image(mlx, "./img/Ground.xpm", &w, &h);
	if (data->img.g == NULL)
		error("Invalid image file : Ground");
	data->img.c = mlx_xpm_file_to_image(mlx, "./img/Apple.xpm", &w, &h);
	if (data->img.w == NULL)
		error("Invalid image file : Collect");
	data->img.p = mlx_xpm_file_to_image(mlx, "./img/Gora.xpm", &w, &h);
	if (data->img.w == NULL)
		error("Invalid image file : Character");
	data->img.e = mlx_xpm_file_to_image(mlx, "./img/Water.xpm", &w, &h);
	if (data->img.w == NULL)
		error("Invalid image file : Exit");
}

int	set_game_data(t_data *data, char key, int x, int y)
{
	if (key == 'C')
		data->m_data.g_data.item_cnt++;
	else if (key == 'P')
	{
		data->m_data.g_data.point_cnt++;
		data->m_data.g_data.pos.x = x;
		data->m_data.g_data.pos.y = y;
	}
	else if (key == 'E')
		data->m_data.g_data.exit_cnt++;
	return (SUCCESS);
}

void	read_game(t_data *data)
{
	int		loop_x;
	int		loop_y;
	char	key;

	loop_x = 0;
	loop_y = 0;
	while (loop_y < data->m_data.y_len)
	{
		loop_x = 0;
		while (loop_x < data->m_data.x_len)
		{
			key = data->m_data.mtx[loop_y][loop_x];
			set_game_data(data, key, loop_x, loop_y);
			loop_x++;
		}
		loop_y++;
	}
}

void	initialize_data(char *argv[], t_data *data)
{
	data->mlx = mlx_init();
	read_map(argv, data);
	read_game(data);
	read_img(data);
}
