/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:50:18 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:50:19 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	init_sprite(t_map *map, int nb_sprite, int i, int j)
{
	if (map->sprite)
	{
		map->sprite[nb_sprite].y
			= ((i + 1) * (map->res_x / 5)) + (map->res_x / 5) / 2;
		map->sprite[nb_sprite].x
			= ((j + 1) * (map->res_x / 5)) + (map->res_x / 5) / 2;
		map->sprite[nb_sprite].degree = 0.000000;
		map->sprite[nb_sprite].x_sprite = 0;
		map->sprite[nb_sprite].size = 0;
		map->sprite[nb_sprite].distance = 0.000000;
		nb_sprite++;
	}
	return (nb_sprite);
}

int	find_sprite(t_map *map)
{
	unsigned int	nb_sprite;
	long int		i;
	long int		j;

	i = 0;
	nb_sprite = 0;
	if (map->lines)
	{
		while (map->lines[i])
		{
			j = 0;
			while (map->lines[i][j])
			{
				if (map->lines[i][j] == '2' && map->nb_sprite > nb_sprite)
				{
					nb_sprite = init_sprite(map, nb_sprite, i, j);
				}
				j++;
			}
			i++;
		}
	}
	return (nb_sprite);
}

void	distance_math(t_map *map, unsigned int nb_sprite, int square_size)
{
	if (map->sprite)
	{
		while (nb_sprite > 0)
		{
			nb_sprite--;
			map->sprite[nb_sprite].distance
				= sqrt(pow((double)map->sprite[nb_sprite].y
						- (square_size * (map->player.pos_y + 1.000000)), 2)
					+ pow((double)map->sprite[nb_sprite].x
						- (square_size * (map->player.pos_x + 1.000000)), 2));
		}
	}
}

void	quicksort_sprite(t_map *map, t_sprite *sprite,
		unsigned int nb_sprite, int square_size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (map->sprite == NULL)
		close_program(map, "Engine can't display sprites.", 2);
	distance_math(map, nb_sprite, square_size);
	nb_sprite = map->nb_sprite;
	if (sprite)
	{
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
}

void	sprite_values_check(t_map *map, unsigned int nb_spt)
{
	if (map->sprite)
	{
		map->sprite[nb_spt].x_sprite = -map->sprite[nb_spt].x_sprite;
		if (cpr_equal(map->sprite[nb_spt].x_sprite, 0.000000))
			map->sprite[nb_spt].x_sprite += 0.000010;
	}
}
