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
				map->sprite[nb_sprite].y = ((i + 1) * map->res_x / 5) + (map->res_x / 5) / 2;
				map->sprite[nb_sprite].x = ((j + 1) * map->res_x / 5) + (map->res_x / 5) / 2;
				map->sprite[nb_sprite].degree = 0;
				map->sprite[nb_sprite].x_sprite = 0;
				map->sprite[nb_sprite].size = 0;
				map->sprite[nb_sprite++].distance = 0;
			}
			j++;
		}
		i++;
	}
	return (nb_sprite);
}

#include <stdio.h>
void	quicksort_sprite(t_sprite *sprite, unsigned int nb_sprite)
{
	unsigned int	i;
	unsigned int	j;
	double		k;

	i = 0;
	j = 0;
	while (nb_sprite > i)
	{
		j = 0;
		while (nb_sprite - i - 1 > j)
		{
			if (sprite[j].distance > sprite[j + 1].distance)
			{
				ft_swap(&sprite[j], &sprite[j + 1]);
			}
			j++;
		}
		i++;
	}
}
