/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:55:10 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/24 20:21:55 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*select_img(char cur, t_data *data)
{
	if (cur == ITEM_KEY[0])
		return (data->img.w);
	else if (cur == ITEM_KEY[1])
		return (data->img.g);
	else if (cur == ITEM_KEY[2])
		return (data->img.c);
	else if (cur == ITEM_KEY[3])
		return (data->img.p);
	else if (cur == ITEM_KEY[4])
		return (data->img.e);
	return (NULL);
}

void	print_draw_map(t_data *data)
{
	int		lx;
	int		ly;
	void	*img;
	void	*m;
	void	*w;

	lx = 0;
	ly = 0;
	m = data->mlx;
	w = data->win;
	while (ly < data->m_data.y_len)
	{
		lx = 0;
		while (lx < data->m_data.x_len)
		{
			img = select_img(data->m_data.mtx[ly][lx], data);
			if (img == data->img.p || img == data->img.c)
				mlx_put_image_to_window(m, w, data->img.g, lx * 64, ly * 64);
			mlx_put_image_to_window(m, w, img, lx * 64, ly * 64);
			lx++;
		}
		ly++;
	}
}

void	print_shall_map(char **map, t_data *data)
{
	int		loop_y;

	loop_y = 0;
	while (loop_y < data->m_data.y_len)
		printf("[%s]\n", map[loop_y++]);
}
