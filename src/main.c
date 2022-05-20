/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suan <suan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:59:24 by suan              #+#    #+#             */
/*   Updated: 2022/05/20 14:05:14 by suan             ###   ########.fr       */
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

int	exit_button(void)
{
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (input_check(ac, av) == FAIL)
		exit(1);
	if (init_game(&game) == FAIL)
		exit(1);
	read_cub(av[1], &game);
	map_check(&game);
	render(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx_win, X_EVENT_KEY_EXIT, 0, exit_button, 0);
	mlx_loop(game.mlx);
	return (0);
}
