#include "cub3D.h"
#include "mlx.h"

enum { VERT, HORIZ };

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
	{1,1,1,1,1}, /* [0][*] */
	{1,0,0,0,1}, /* [1][*] */
	{1,0,0,0,1}, /* [2][*] */
	{1,1,0,0,1}, /* and so on... */
	{1,1,0,0,1},
	{1,1,1,1,1}
};

//chk
int	map_get_cell( int x, int y )
{
	if ((x >= 0 && x < MAPX) \
		&& (y >= 0 && y < MAPY))
		return map[x][y];
	else
		return (-1);
}

void init_sect(t_sector *sect, double ray)
{
	ft_memset(sect, 0, sizeof(sect));
	sect->xstep = sgn(cos(ray));  /* +1 (right), 0 (no change), -1 (left) */
	sect->ystep = sgn(sin(ray));  /* +1 (up),    0 (no change), -1 (down) */
	if (sect->xstep == 0)
		sect->xslope = INFINITY;
	else
		sect->xslope = tan(ray);
	
	if (sect->ystep == 0)
		sect->yslope = INFINITY;
	else
		sect->yslope = 1./tan(ray);
}

void next_init(player_t pl, t_pos *next, t_sector sect)
{
	if (sect.xstep > 0)
		next->pos_x = floor(pl.px)+1;
	else if (sect.xstep < 0)
		next->pos_x = ceil(pl.px)-1;
	else 
		next->pos_x = pl.px;
	if (sect.ystep > 0)
		next->pos_y = floor(pl.py)+1;
	else if (sect.ystep < 0)
		next->pos_y = ceil(pl.py)-1;
	else 
		next->pos_y = pl.py;
}

bool get_wall_intersection( double ray, player_t pl, dir_t* wdir, t_pos *wpos)
{
	t_sector	sect;
	t_pos		next;
	double f=INFINITY, g=INFINITY;

	// f , g, hit side mapx mapy dist-h dist-v

	bool hit = false;
	int hit_side; /* either VERT or HORIZ */
	init_sect(&sect, ray);
	next_init(pl, &next, sect);
	while( !hit )
	{
		int mapx, mapy;
		if( sect.xstep != 0 ) 
			f = sect.xslope * (next.pos_x-pl.px) + pl.py;
		if( sect.ystep != 0 ) 
			g = sect.yslope * (next.pos_y-pl.py) + pl.px;
		
		/* which is nearer to me - VERT(next.pos_x,f) or HORIZ(g,next.pos_y)? */
		double dist_v = l2dist(pl.px, pl.py, next.pos_x, f);
		double dist_h = l2dist(pl.px, pl.py, g, next.pos_y);

		if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
			mapx = (sect.xstep == 1) ? (int)(next.pos_x) : (int)(next.pos_x)-1 ;
			mapy = (int) f;
			hit_side = VERT;
			printf(" V(%d, %.2f) ->", mapx, f);
		}
		else {  /* HORIZ is nearer; go along y-axis */
			mapx = (int) g;
			mapy = (sect.ystep == 1) ? (int)(next.pos_y) : (int)(next.pos_y)-1 ;
			hit_side = HORIZ;
			printf(" H(%.2f, %d) ->", g, mapy);
		}

		int cell = map_get_cell(mapx, mapy);
		if( cell < 0 ) break;   /* out of map */
		if( cell == 1 ) {   /* hit wall? */
			if( hit_side == VERT ) {
				*wdir = (sect.xstep > 0) ? DIR_W : DIR_E;
				wpos->pos_x = next.pos_x;
				wpos->pos_y = f;
			}
			else { /* HORIZ */
				*wdir = (sect.ystep > 0) ? DIR_S : DIR_N;
				wpos->pos_x = g;
				wpos->pos_y = next.pos_y;
			}
			hit = true;
			printf(" hit wall!\n");
			break;
		}
		if( hit_side == VERT ) next.pos_x += sect.xstep;
		else next.pos_y += sect.ystep;
	}
	/* end of while(!hit) */
	return hit;
}

int        key_press(int keycode, t_game *game)
{    
	if( keycode == KEY_LEFT || keycode == KEY_RIGHT )
	{
		if (keycode == KEY_LEFT)
			player_rotate(&game->pl, ROT_UNIT);
		else
			player_rotate(&game->pl, -1 * ROT_UNIT);
		render(game);
	}
	else if( keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D )
	{
		if( player_move(&game->pl, keycode, MOVE_UNIT) == 0 ) 
			render(game);
	}
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int        exit_button(void)
{
	exit(0);
}

int game_initialize(t_game *game, char** av)
{
	game->pl.px = atof(av[1]);
	game->pl.py = atof(av[2]);
	game->pl.th = deg2rad(atof(av[3]));
	game->mlx = mlx_init();
	game->fov_h = deg2rad(FOV);
	game->fov_v = (game->fov_h * (double)SY / (double)SX);
	game->per_angle = game->fov_h / (SX-1.);
	if (game->mlx == NULL)
		return (0);
	game->mlx_win = mlx_new_window(game->mlx, SX, SY, "cub3D"); 
	if (game->mlx_win == NULL)
		return (0);
	game->img.img = mlx_new_image(game->mlx, SX, SY);
	if (game->img.img == NULL)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	if (game->img.addr == NULL)
		return (0);
	return (1);
}

int input_check(int ac, char** av)
{
	if( ac != 4 ) {
		fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
		return (0);
	}
	return (1);
}

int	main(int ac, char** av)
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