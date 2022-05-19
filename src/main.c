/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:59:24 by suan              #+#    #+#             */
/*   Updated: 2022/05/19 19:10:46 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
			player_rotate(&game->pl, ROT_UNIT);
		else
			player_rotate(&game->pl, -1 * ROT_UNIT);
		render(game);
	}
	else if (keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D)
	{
		if (player_move(game, keycode, MOVE_UNIT) == 0)
			render(game);
	}
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	exit_button(t_game *game)
{
	exit(0);
}

/* 제거 */
static char	g_map[MAPY][MAPX] = {
	{'1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '1'},
	{'1', '1', ' 1', '1', '1'}
};
/* 여기까지 */

int	init_game(t_game *game, char **av)
{
	game->pl.px = atof(av[1]);
	game->pl.py = atof(av[2]);
	game->pl.th = deg2rad(atof(av[3]));
	/* 제거 */
	game->map.mapX = MAPX;
	game->map.mapY = MAPY;
	for (int y = 0; y < MAPY; y++)
		for (int x = 0; x < MAPX; x++)
			game->map.map[y][x] = g_map[y][x];
	/* 여기까지 */	
	int loop = 0;
	while (loop < 1000)
		ft_memset(game->map.chk[loop++], 0, sizeof(char) * 1000);
	game->mlx = mlx_init();
	game->fov_h = deg2rad(FOV);
	game->fov_v = (game->fov_h * (double)SY / (double)SX);
	game->per_angle = game->fov_h / (SX - 1.);
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

int	main(int ac, char **av)
{
	t_game	game;

	if (input_check(ac, av) == FAIL)
		exit(1);
	if (init_game(&game, av) == FAIL)
		exit(1);
	map_check(&game);
	load_texture(&game);
	render(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx_win, X_EVENT_KEY_EXIT, 0, exit_button, &game);
	mlx_loop(game.mlx);
	return (0);
}
