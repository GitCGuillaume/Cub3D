#include "../../includes/cub.h"

void	degree_check_divide(t_map *map, int nb_spt)
{
	double	degree;

	degree = radian_to_degree(map->sprite[nb_spt].degree);
	if (cpr_equal(degree, 0.0)
			|| cpr_equal(degree, 90.0)
			|| cpr_equal(degree, 180.0)
			|| cpr_equal(degree, 270.0))
		map->sprite[nb_spt].degree =
			radian_to_degree(map->sprite[nb_spt].degree) + 0.000010;
}
