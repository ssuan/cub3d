#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53

# define KEY_EVENT_PRESS    2
# define KEY_EVENT_EXIT        17

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

#define  SX         400     /* screen width */
#define  SY         250     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define  _2PI       6.28318530717958647692  /* 2 * M_PI */

#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1

//enum { KEY_OTHER, KEY_W, KEY_A, KEY_S, KEY_D, KEY_LEFT, KEY_RIGHT, KEY_ESC };

typedef struct {
	double px;
	double py;
	double th;
} player_t;

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

enum { VERT, HORIZ };

typedef enum { false=0, true=1 } bool;
typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

#define  MAPX   6
#define  MAPY   5

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
	{1,1,1,1,1}, /* [0][*] */
	{1,0,0,0,1}, /* [1][*] */
	{1,0,0,0,1}, /* [2][*] */
	{1,1,0,0,1}, /* and so on... */
	{1,1,0,0,1},
	{1,1,1,1,1}
};

int
map_get_cell( int x, int y )
{
	return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int
sgn( double d )
{
	return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double
l2dist( double x0, double y0, double x1, double y1 )
{
	double dx = x0 - x1;
	double dy = y0 - y1;
	return sqrt(dx*dx + dy*dy);
}

bool
get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
	int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
	int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

	double xslope = (xstep == 0) ? INFINITY : tan(ray);
	double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

	double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
	double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

	printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
		rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

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
double
cast_single_ray( int x, player_t pl, dir_t* pdir )
{
	double ray = (pl.th + FOVH_2) - (x * ANGLE_PER_PIXEL);

	dir_t wdir;     /* direction of wall */
	double wx, wy;  /* coord. of wall intersection point */

	if( get_wall_intersection(ray, pl.px, pl.py, &wdir, &wx, &wy) == false )
		return INFINITY; /* no intersection - maybe bad map? */

	double wdist = l2dist(pl.px, pl.py, wx, wy);
	wdist *= cos(pl.th - ray);  /* 보정 */

	return wdist;
}

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	player_t pl;
	t_data	img;
} t_game;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void
player_rotate( player_t* pp, double th )
{
    pp->th += th;
    if( pp->th < 0 ) pp->th += _2PI;
    else if( pp->th > _2PI ) pp->th -= _2PI;
}


int
get_wall_height( double dist )
{
	double fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return (int)(SY * (WALL_H / fov_h)); /* in pixels */
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


void
render( t_game *game )
{
	static int wall_colors[] = {    /* DIR_N, E, W, S */
		0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
	};

	for (int i = 0; i < SX; i++) 
		for (int j = 0; j < SY; j++)
			my_mlx_pixel_put(&game->img, i, j, 0xFFFFFF);

	for( int x=0; x<SX; x++ ) {
		dir_t wdir;
		double wdist = cast_single_ray(x, game->pl, &wdir);
		draw_wall(game->img, wdist, x, wall_colors[wdir % 5]);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

static int
get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

int
player_move( player_t* pp, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

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

int        key_press(int keycode, t_game *game)
{    
	if( keycode == KEY_LEFT || keycode == KEY_RIGHT ) {
		player_rotate(&game->pl, ROT_UNIT * (keycode==KEY_LEFT ? 1 : -1));
		render(game);
	}
	else if( keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D ) {
		if( player_move(&game->pl, keycode, MOVE_UNIT) == 0 ) {
			render(game);
		}
	}
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int        exit_button(void)
{
	exit(0);
}


int
main( int ac, char** av )
{
	t_game game;

	if( ac != 4 ) {
		fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
		exit(1);
	}

	game.pl.px = atof(av[1]);
	game.pl.py = atof(av[2]);
	game.pl.th = deg2rad(atof(av[3]));



	double px, py, th;
	px = atof(av[1]);
	py = atof(av[2]);
	th = deg2rad(atof(av[3]));

	// /* print map */
	// for( int y=MAPY-1; y>=0; y-- ) {
	// 	for( int x=0; x<MAPX; x++ ) {
	// 		printf("%c ", (map_get_cell(x,y)==1 ? '#':'.'));
	// 	}
	// 	putchar('\n');
	// }

	// for( int x=0; x<SX; x++ ) {
	// 	dir_t wdir;
	// 	double wdist = cast_single_ray(x, px, py, th, &wdir);
	// 	printf("** ray %3d : dist %.2f\n", x, wdist);
	// }

	/* ... 중간생략 ... */

	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, SX, SY, "cub3D"); 
	game.img.img = mlx_new_image(game.mlx, SX, SY);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);

	render(&game);

	// for( int x=0; x<SX; x++ ) {
	//     dir_t wdir;
	//     double wdist = cast_single_ray(x, game.pl, &wdir);
	//     draw_wall(game.img, wdist, x, 0x999999);//wall_colors[wdir]);
	// }

	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, KEY_EVENT_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx_win, KEY_EVENT_EXIT, 0, exit_button, &game);
	mlx_loop(game.mlx);

	return 0;
}