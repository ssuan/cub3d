/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:22:07 by suan              #+#    #+#             */
/*   Updated: 2022/05/18 22:21:36 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_image(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->w, &img->h);
	// if (!img->img)
	// {
	// 	fprintf(stderr, "image not found\n");
	// 	exit(1);
	// }
	if (!img->img)
		error("*.cub file has Invalid xpm PATH");
	img->data = (unsigned int *)mlx_get_data_addr(img->img, &img->bpp, \
			&img->size_l, &img->endian);
}

void	load_texture(t_game *game)
{
	load_image(game, &game->wall[0], "texture/wall_n.xpm");
	load_image(game, &game->wall[1], "texture/wall_e.xpm");
	load_image(game, &game->wall[2], "texture/wall_w.xpm");
	load_image(game, &game->wall[3], "texture/wall_s.xpm");
}
