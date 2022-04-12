/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools_two_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:50:25 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:50:26 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			map->sprite[nb_spt].degree
				= map->sprite[nb_spt].degree + 0.000010;
		}
	}
}

void	write_in_image_one(t_map *map, int u, int v, int pixel)
{
	if (map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 0])
		map->image[0].mlx_get_data[pixel + 0]
			= map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 0];
	if (map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 1])
		map->image[0].mlx_get_data[pixel + 1]
			= map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 1];
	if (map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 2])
		map->image[0].mlx_get_data[pixel + 2]
			= map->image[5].mlx_get_data[((v * map->image[5].line_bytes)
				+ (u * (map->image[5].bpp >> 3))) + 2];
}

void	write_in_image_two(t_map *map, int u, int v, int pixel)
{
	if (map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 0])
		map->image[0].mlx_get_data[pixel + 0]
			= map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 0];
	if (map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 1])
		map->image[0].mlx_get_data[pixel + 1]
			= map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 1];
	if (map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 2])
		map->image[0].mlx_get_data[pixel + 2]
			= map->image[6].mlx_get_data[((v * map->image[6].line_bytes)
				+ (u * (map->image[6].bpp >> 3))) + 2];
}

void	tick_handler(t_map *map)
{
	map->tick = map->tick + 1;
	if (map->tick >= 60)
		map->tick = 0;
}

void	print_sprite(t_map *map, int pixel, int nb_sprite, int height)
{
	int	u;
	int	v;
	int	size;

	u = map->sprite[nb_sprite].u;
	size = (int)floor(map->sprite[nb_sprite].size);
	v = ((height - (map->res_y + size) / 2)
			+ size) * map->image[5].height / size;
	if (map->image[5].mlx_get_data)
	{
		write_in_image_one(map, u, v, pixel);
	}
}
