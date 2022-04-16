/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:16 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/25 18:26:53 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	walk_process(int x, int y, t_data *data)
{
	t_pos	*cur;

	cur = &data->m_data.g_data.pos;
	data->m_data.mtx[cur->y][cur->x] = '0';
	if (data->m_data.mtx[y][x] == ITEM_KEY[2])
		data->m_data.g_data.item_cnt--;
	data->m_data.mtx[y][x] = 'P';
	cur->x = x;
	cur->y = y;
}

int	walk_check(int x, int y, t_data *data)
{
	t_pos	pos;
	char	check;

	pos.x = data->m_data.g_data.pos.x + x;
	pos.y = data->m_data.g_data.pos.y + y;
	check = data->m_data.mtx[pos.y][pos.x];
	if (check == ITEM_KEY[0])
		return (0);
	if (check == ITEM_KEY[1] || check == ITEM_KEY[2])
	{
		walk_process(pos.x, pos.y, data);
		return (1);
	}
	if (check == ITEM_KEY[4] && data->m_data.g_data.item_cnt != 0)
		return (0);
	if (check == ITEM_KEY[4] && data->m_data.g_data.item_cnt <= 0)
	{
		printf("GAME CLEAR\n");
		exit(0);
		return (0);
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	int		x;
	int		y;
	int		flag;

	x = 0;
	y = 0;
	if (keycode == KEY_W || keycode == KEY_UP)
		y = -1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		y = 1;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		x = -1;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		x = 1;
	if (keycode == KEY_ESC)
		close_map();
	flag = walk_check(x, y, data);
	print_draw_map(data);
	if (flag != 0)
		printf("STEP CNT[%d]\n", data->m_data.g_data.step_cnt++);
	return (SUCCESS);
}
