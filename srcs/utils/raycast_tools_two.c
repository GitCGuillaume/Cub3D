#include "../../includes/cub.h"

size_t	max_lines(t_map *map)
{
	size_t i;

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
	if (value > 359.00)
		value -= 360.0;
	else if (value < 0.0)
		value += 360.0;
	return (value);
}
