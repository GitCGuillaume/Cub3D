/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:30:08 by gchopin           #+#    #+#             */
/*   Updated: 2021/02/03 17:30:09 by gchopin          ###   ########.fr       */
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
	free(map->z_buffer);
	map->z_buffer=NULL;
	close_program(map, "every floor colour rgb must be between 0 and 255\n", 2);
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
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
			&& (b >= 0 && b <= 255))
	{
		colour = r << 16;
		colour += g << 8;
		colour += b;
		map->ceiling_colour = colour;
		return (mlx_get_color_value(map->mlx_ptr, colour));
	}
	free(map->z_buffer);
	map->z_buffer=NULL;
	close_program(map, "every ceil colour rgb must be between 0 and 255\n", 2);
	return (0);
}
