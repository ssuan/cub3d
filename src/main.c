/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:59:24 by suan              #+#    #+#             */
/*   Updated: 2022/05/15 17:27:21 by suan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 빼기
static int	g_map[MAPX][MAPY] = {
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1}
};

//chk
int	map_get_cell( int x, int y )
{
	if ((x >= 0 && x < MAPX) \
		&& (y >= 0 && y < MAPY))
		return (g_map[x][y]);
	else
		return (-1);
}

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
		if (player_move(&game->pl, keycode, MOVE_UNIT) == 0)
			render(game);
	}
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	exit_button(void)
{
	exit(0);
}

int	game_initialize(t_game *game, char **av)
{
	game->pl.px = atof(av[1]);
	game->pl.py = atof(av[2]);
	game->pl.th = deg2rad(atof(av[3]));
	game->mlx = mlx_init();
	game->fov_h = deg2rad(FOV);
	game->fov_v = (game->fov_h * (double)SY / (double)SX);
	game->per_angle = game->fov_h / (SX - 1.);
	if (game->mlx == NULL)
		return (0);
	game->mlx_win = mlx_new_window(game->mlx, SX, SY, "cub3D");
	if (game->mlx_win == NULL)
		return (0);
	game->img.img = mlx_new_image(game->mlx, SX, SY);
	if (game->img.img == NULL)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, \
		&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	if (game->img.addr == NULL)
		return (0);
	return (1);
}

int	input_check(int ac, char **av)
{
	if (ac != 4)
	{
		fprintf(stderr, "usage: %s x y th(deg)\n", av[0]);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (input_check(ac, av) == 0)
		exit(1);
	if (game_initialize(&game, av) == 0)
		exit(1);
	render(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx_win, X_EVENT_KEY_EXIT, 0, exit_button, &game);
	mlx_loop(game.mlx);
	return (0);
}
