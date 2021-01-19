#include "../../includes/cub.h"

int	find_sprite(t_map *map)
{
	long int	i;
	long int	j;
	unsigned int		nb_sprite;

	i = 0;
	j = 0;
	nb_sprite = 0;
	while (map->lines[i])
	{
		j = 0;
		while (map->lines[i][j])
		{
			if (map->lines[i][j] == '2' && map->nb_sprite > nb_sprite)
			{
				map->sprite[nb_sprite].y = ((i + 1) * map->res_x / 5);
				map->sprite[nb_sprite].x = ((j + 1) * map->res_x / 5);
				map->sprite[nb_sprite].degree = 0;
				map->sprite[nb_sprite].x_sprite = 0;
				map->sprite[nb_sprite++].distance = 0;
			}
			j++;
		}
		i++;
	}
	return (i);
}
