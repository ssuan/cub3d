/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:47:33 by sunbchoi          #+#    #+#             */
/*   Updated: 2022/05/19 19:56:04 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_value(t_game *game)
{
	int	loop;

	game->pl.px = -1.0;
	game->pl.py = -1.0;
	game->map.ceil_color = -1;
	game->map.floor_color = -1;
	game->fov_h = deg2rad(FOV);
	game->fov_v = (game->fov_h * (double)SY / (double)SX);
	game->per_angle = game->fov_h / (SX - 1.);
	loop = 0;
	while (loop < 1000)
	{
		ft_memset(game->map.chk[loop], 0, sizeof(char) * 1000);
		ft_memset(game->map.map[loop++], 0, sizeof(char) * 1000);
	}
}

int	init_game(t_game *game)
{	
	init_value(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (FAIL);
	game->mlx_win = mlx_new_window(game->mlx, SX, SY, "cub3D");
	if (game->mlx_win == NULL)
		return (FAIL);
	game->img.img = mlx_new_image(game->mlx, SX, SY);
	if (game->img.img == NULL)
		return (FAIL);
	game->img.addr = mlx_get_data_addr(game->img.img, \
		&game->img.bpp, &game->img.size_l, &game->img.endian);
	if (game->img.addr == NULL)
		return (FAIL);
	return (SUCCESS);
}
