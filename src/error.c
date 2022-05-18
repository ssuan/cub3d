#include "cub3D.h"

int	error(char *msg)
{
	printf("\e[31m\e[1mError\n%s \e[0m \n", msg);
	exit (1);
	return (0);
}