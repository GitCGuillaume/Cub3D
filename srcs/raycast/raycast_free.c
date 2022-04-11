#include "../../includes/cub.h"

void	check_distance(t_map *map)
{
	if (map->player.ray_horizontal.distance_wall > 2147483646.000000
			|| map->player.ray_vertical.distance_wall > 2147483646.000000)
	{
		close_program(map, "distances values are wrong.\n", 2);
	}
}
