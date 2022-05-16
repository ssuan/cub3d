/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi@student.42seoul.kr <sunbchoi>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:59:24 by suan              #+#    #+#             */
/*   Updated: 2022/05/16 22:06:14 by sunbchoi@st      ###   ########.fr       */
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
		if (player_move(&game->pl, keycode, MOVE_UNIT) == 0)
			render(game);
	}
	if (keycode == KEY_ESC)
	{
		for (int i = 0; i < 4; i++)
			mlx_destroy_image(game->mlx, game->wall[i].img);
		exit(0);
	}
	return (0);
}

int	exit_button(void)
{
//	mlx_destroy_image(game->mlx, img->img);
	exit(0);
}

int	game_initialize(t_game *game, char **av)
{
	// game->pl.px = atof(av[1]);
	// game->pl.py = atof(av[2]);
	// game->pl.th = deg2rad(atof(av[3]));
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
	// if (ac != 4)
	// {
	// 	fprintf(stderr, "usage: %s x y th(deg)\n", av[0]);
	// 	return (0);
	// }
	
	char	*map_ext;

	if (ac < 2 || ft_strlen(av[1]) == 0)
	{
		perror("Please enter the name of the map file you want to use.\n\
			Ex: ./maps/map.cub");
	}
	else if (ac > 2)
	{
		perror("Too many argument entered. Please retry it again.\n\
			Ex: ./maps/map.cub");
	}
	map_ext = ft_strrchr(av[1], '.');
	if ((ft_strstr(map_ext, ".cub") == NULL) \
		|| (ft_strlen(map_ext) != ft_strlen(".cub")))
		perror("Invalid map extension. Please Enter *.cub");
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (input_check(ac, av) == 0)
		exit(1);
	map_check();
	if (game_initialize(&game, av) == 0)
		exit(1);
	load_texture(&game);
	render(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx_win, X_EVENT_KEY_EXIT, 0, exit_button, &game);
	mlx_loop(game.mlx);
	return (0);
}
