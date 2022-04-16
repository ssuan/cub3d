/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:31:00 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 14:02:11 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(t_data *data)
{
	int		loop_y;
	int		loop_x;

	loop_y = 0;
	while (loop_y < data->m_data.y_len)
	{
		loop_x = 0;
		if (loop_y == 0 || loop_y == (data->m_data.y_len - 1))
		{
			while (data->m_data.mtx[loop_y][loop_x])
			{
				if (data->m_data.mtx[loop_y][loop_x] != '1')
					error("Invalid map: top or bottom is not wall");
				loop_x++;
			}
		}
		if (data->m_data.mtx[loop_y][0] != '1'
			|| data->m_data.mtx[loop_y][data->m_data.x_len - 1] != '1')
			error("Invalid map: side is not wall");
		loop_y++;
	}
	return (1);
}

int	check_has(t_data *data)
{
	if (data->m_data.g_data.exit_cnt == 0)
		error("Invalid map: This map has not Exit");
	if (data->m_data.g_data.item_cnt == 0)
		error("Invalid map: This map has not Item");
	if (data->m_data.g_data.point_cnt == 0)
		error("Invalid map: This map has not Character");
	if (data->m_data.g_data.point_cnt > 1)
		error("Invalid map: This map has Too many Character");
	return (1);
}

int	check_ret(t_data *data)
{
	int		loop_y;

	loop_y = 0;
	while (loop_y < data->m_data.y_len)
	{
		if (data->m_data.x_len != (int)ft_strlen(data->m_data.mtx[loop_y]))
			error("Invalid map: This map is not a retangle");
		loop_y++;
	}
	return (1);
}

int	check_char(t_data *data)
{
	int		loop_y;
	int		loop_x;
	char	check;

	loop_y = 0;
	while (loop_y < data->m_data.y_len)
	{
		loop_x = 0;
		while (data->m_data.mtx[loop_y][loop_x])
		{
			check = data->m_data.mtx[loop_y][loop_x];
			if (ft_strchr(ITEM_KEY, check) == NULL)
				error("Invalid map: This map has unknown char");
			loop_x++;
		}
		loop_y++;
	}
	return (1);
}

int	check_map(t_data *data)
{
	check_walls(data);
	check_has(data);
	check_ret(data);
	check_char(data);
	return (0);
}
