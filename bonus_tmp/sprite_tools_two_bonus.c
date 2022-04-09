#include "cub_bonus.h"

void	degree_check_divide(t_map *map, int nb_spt)
{
	double	degree;

	degree = map->sprite[nb_spt].degree;
	if (cpr_equal(degree, 0.000000)
			|| cpr_equal(degree, 90.000000)
			|| cpr_equal(degree, 180.000000)
			|| cpr_equal(degree, 270.000000))
	{
		if (map->sprite)
		{
			map->sprite[nb_spt].degree =
				map->sprite[nb_spt].degree + 0.000010;
		}
	}
}
