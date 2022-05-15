#include "cub3D.h"
#include "mlx.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);

enum { VERT, HORIZ };

int wall_colors[] = {    /* DIR_N, E, W, S */
		0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
	};

typedef enum { false=0, true=1 } bool;
typedef enum { DIR_N=0, DIR_E=1, DIR_W=2, DIR_S=3 } dir_t;

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
	{1,1,1,1,1}, /* [0][*] */
	{1,0,0,0,1}, /* [1][*] */
	{1,0,0,0,1}, /* [2][*] */
	{1,1,0,0,1}, /* and so on... */
	{1,1,0,0,1},
	{1,1,1,1,1}
};

int	map_get_cell( int x, int y )
{
	if ((x >= 0 && x < MAPX) \
		&& (y >= 0 && y < MAPY))
		return map[x][y];
	else
		return (-1);
}

bool get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
	int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
	int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

	double xslope = (xstep == 0) ? INFINITY : tan(ray);
	double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

	double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
	double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);
	
	double f=INFINITY, g=INFINITY;
	bool hit = false;
	int hit_side; /* either VERT or HORIZ */

	while( !hit )
	{
		int mapx, mapy;

		if( xstep != 0 ) f = xslope * (nx-px) + py;
		if( ystep != 0 ) g = yslope * (ny-py) + px;

		/* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
		double dist_v = l2dist(px, py, nx, f);
		double dist_h = l2dist(px, py, g, ny);

		if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
			mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
			mapy = (int) f;
			hit_side = VERT;
			printf(" V(%d, %.2f) ->", mapx, f);
		}
		else {  /* HORIZ is nearer; go along y-axis */
			mapx = (int) g;
			mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
			hit_side = HORIZ;
			printf(" H(%.2f, %d) ->", g, mapy);
		}
		int cell = map_get_cell(mapx, mapy);
		if( cell < 0 ) break;   /* out of map */

		if( cell == 1 ) {   /* hit wall? */
			if( hit_side == VERT ) {
				*wdir = (xstep > 0) ? DIR_W : DIR_E;
				*wx = nx;
				*wy = f;
			}
			else { /* HORIZ */
				*wdir = (ystep > 0) ? DIR_S : DIR_N;
				*wx = g;
				*wy = ny;
			}
			hit = true;
			printf(" hit wall!\n");
			break;
		}

		if( hit_side == VERT ) nx += xstep;
		else ny += ystep;
	}
	/* end of while(!hit) */

	return hit;
}


double	cast_single_ray(int x, player_t pl, dir_t *wdir)
{
	double	ray;
	double	wx;
	double	wy;

	ray = (pl.th + FOV_H / 2.0) - (x * ANGLE_PER_PIXEL);
	if( get_wall_intersection(ray, pl.px, pl.py, wdir, &wx, &wy) == false )
		return (INFINITY); /* no intersection - maybe bad map? */

	double wdist = l2dist(pl.px, pl.py, wx, wy);
	wdist *= cos(pl.th - ray);  /* 보정 */

	return (wdist);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	player_rotate( player_t* pp, double th )
{
    pp->th += th;
    if (pp->th < 0)
		pp->th += _2PI;
	else if( pp->th > _2PI )
		pp->th -= _2PI;
}


int	get_wall_height( double dist )
{
	double fov_h;

	fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return ((int)(SY * (WALL_H / fov_h))); /* in pixels */
}


void
draw_wall( t_data img, double wdist, int x, int color )
{
	int wh = get_wall_height(wdist);    /* wall height, in pixels */

	/* starting/ending y pos of the wall slice */
	int y0 = (int)((SY - wh)/2.0);
	int y1 = y0 + wh - 1;

	/* needs clipping */
	int ystart = max(0, y0);
	int yend = min(SY-1, y1);

	for (int i = ystart; i < yend; i++)
	{
		my_mlx_pixel_put(&img, x, i, color);
	}
}


void	render( t_game *game )
{
	int loop;
	int loop2;
	dir_t wdir;
	double wdist;

	loop = 0;
	loop2 = 0;
	while (loop < SX)
	{
		while (loop2 < SY)
		{
			my_mlx_pixel_put(&game->img, loop, loop2, 0xFFFFFF);
			loop2++;
		}
		loop2 = 0;
		loop++;
	}
	loop = 0;
	while (loop < SX)
	{
		wdist = cast_single_ray(loop, game->pl, &wdir);
		draw_wall(game->img, wdist, loop, wall_colors[wdir]);
		loop++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

static int get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
	int sgn;

	if (key == KEY_W || key == KEY_A)
		sgn = 1;
	else
		sgn = -1;
    if (key == KEY_W || key == KEY_S)
	{
		*pdx = sgn * amt * cos(th);
        *pdy = sgn * amt * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
	    *pdx = amt * cos(th + sgn * M_PI_2);
        *pdy = amt * sin(th + sgn * M_PI_2);
    }
	else
		return (-1);
	return (0);
}

int player_move( player_t* pp, int key, double amt )
{
    double	dx; 
	double	dy;
    double	nx;
	double	ny;

    if( get_move_offset(pp->th, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = pp->px + dx;
    ny = pp->py + dy;

    if( map_get_cell((int)nx, (int)ny) != 0 ) {
        printf("** bump !\n");
        return -1;
    }
    pp->px = nx;
    pp->py = ny;
    return 0;
}

int	key_press(int keycode, t_game *game)
{    
	if( keycode == KEY_LEFT || keycode == KEY_RIGHT )
	{
		if (keycode == KEY_LEFT)
			player_rotate(&game->pl, ROT_UNIT);
		else
			player_rotate(&game->pl, -ROT_UNIT);	
		render(game);
	}
	else if( keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D )
	{
		if(player_move(&game->pl, keycode, MOVE_UNIT) == 0) 
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
