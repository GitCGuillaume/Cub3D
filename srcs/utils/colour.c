/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:30:08 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 09:57:33 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

unsigned int	manage_bit_colour_floor(t_map *map)
{
	int	colour;
	int	r;
	int	g;
	int	b;

	colour = 0;
	if (!map->colour[0] || !map->colour[1] || !map->colour[2])
		close_program(map, "Couldn't get floors colours from map.\n", 2);
	r = ft_atoi(map->colour[0]);
	g = ft_atoi(map->colour[1]);
	b = ft_atoi(map->colour[2]);
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
		&& (b >= 0 && b <= 255))
	{
		colour = r << 16;
		colour += g << 8;
		colour += b;
		map->floor_colour = colour;
		return (mlx_get_color_value(map->mlx_ptr, colour));
	}
	close_program(map, "every floor colours rgb must be between 0 and 255\n", 2);
	return (0);
}

unsigned int	manage_bit_colour_ceil(t_map *map)
{
	int	colour;
	int	r;
	int	g;
	int	b;

	colour = 0;
	r = ft_atoi(map->colour[3]);
	g = ft_atoi(map->colour[4]);
	b = ft_atoi(map->colour[5]);
	if (!map->colour[3] || !map->colour[4] || !map->colour[5])
		close_program(map, "Couldn't get ceils colours from map.\n", 2);
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
		&& (b >= 0 && b <= 255))
	{
		colour = r << 16;
		colour += g << 8;
		colour += b;
		map->ceiling_colour = colour;
		return (mlx_get_color_value(map->mlx_ptr, colour));
	}
	close_program(map, "every ceil colour rgb must be between 0 and 255\n", 2);
	return (0);
}
