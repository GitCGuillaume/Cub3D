#include "../../includes/cub.h"

size_t	max_lines(t_map *map)
{
	size_t	i;

	i = 0;
	if (map->lines)
	{
		while (map->lines[i])
		{
			i++;
		}
	}
	return (i);
}

double	correct_distance(double value)
{
	if (value > 359.000000)
		value -= 360.000000;
	else if (value < 0.000000)
		value += 360.000000;
	return (value);
}
