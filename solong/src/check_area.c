/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:32:10 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/24 21:31:41 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	emptying_map(char **map, t_data *data)
{
	int		ly;
	int		lx;

	ly = 0;
	while (ly < data->m_data.y_len)
	{
		lx = 0;
		while (lx < data->m_data.x_len)
		{
			if (map[ly][lx] == ITEM_KEY[2] || map[ly][lx] == ITEM_KEY[3]
			|| map[ly][lx] == ITEM_KEY[4])
				map[ly][lx] = ITEM_KEY[1];
			lx++;
		}
		ly++;
	}
}

char	**create_empty_map(t_data *data)
{
	char	**cpy_map;
	int		ly;
	int		x_len;

	cpy_map = (char **)ft_calloc(sizeof(char *), data->m_data.y_len + 1);
	x_len = data->m_data.x_len;
	ly = 0;
	while (ly < data->m_data.y_len)
	{
		cpy_map[ly] = ft_calloc(sizeof(char), x_len + 1);
		ft_memmove(cpy_map[ly], data->m_data.mtx[ly], x_len);
		cpy_map[ly][data->m_data.x_len] = 0;
		ly++;
	}
	emptying_map(cpy_map, data);
	return (cpy_map);
}

void	setting_empty_map(char **empty_map, int x, int y)
{
	int		add;
	int		plan_loop;

	if (empty_map[y][x] == ITEM_KEY[0] || empty_map[y][x] == ITEM_KEY[2])
		return ;
	if (empty_map[y][x] == ITEM_KEY[1])
		empty_map[y][x] = 'C';
	plan_loop = 0;
	while (plan_loop < 4)
	{
		if (plan_loop % 2 == 0)
			add = -1;
		else
			add = 1;
		if (plan_loop / 2 == 0 && (empty_map[y][x + add] == ITEM_KEY[1]))
			setting_empty_map(empty_map, x + add, y);
		else if (plan_loop / 2 == 1 && (empty_map[y + add][x] == ITEM_KEY[1]))
			setting_empty_map(empty_map, x, y + add);
		plan_loop++;
	}
}

int	checking_empty_map(char **empty_map, t_data *data)
{
	int	loop_y;

	loop_y = 0;
	while (loop_y < data->m_data.y_len)
	{
		if (ft_strchr(empty_map[loop_y], '0') != NULL)
		{
			print_shall_map(empty_map, data);
			error("There are can't to go area that this map\n");
		}
		loop_y++;
	}
	return (SUCCESS);
}

int	check_area(t_data *data)
{
	t_pos	cur;
	char	**empty_map;

	cur = data->m_data.g_data.pos;
	empty_map = create_empty_map(data);
	setting_empty_map(empty_map, cur.x, cur.y);
	empty_map[cur.y][cur.x] = ITEM_KEY[3];
	checking_empty_map(empty_map, data);
	return (SUCCESS);
}
