/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:10:12 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 16:56:40 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	print_sprite_2(t_map *map, int pixel, int nb_sprite, int height)
{
	int	u;
	int	v;
	int	size;

	u = map->sprite[nb_sprite].u;
	size = (int)floor(map->sprite[nb_sprite].size);
	v = ((height - (map->res_y + size) / 2)
			+ size) * map->image[6].height / size;
	if (map->image[6].mlx_get_data)
	{
		write_in_image_two(map, u, v, pixel);
	}
}

void	while_height(t_map *map, int bottom, int nb_sprite, int width_left)
{
	int	height;
	int	size;

	if (map->sprite)
	{
		size = (int)floor(map->sprite[nb_sprite].size);
		height = (map->res_y >> 1) - (size >> 1);
		if (height < 0)
			height = 0;
		while (width_left < map->res_x
			&& bottom > height && map->sprite[nb_sprite].distance
			* (map->res_x / 5) < *(map->z_buffer + width_left))
		{
			if (map->tick <= 30)
				print_sprite(map,
					(height * map->image[0].line_bytes)
					+ (width_left * 4), nb_sprite, height);
			else
				print_sprite_2(map,
					(height * map->image[0].line_bytes)
					+ (width_left * 4), nb_sprite, height);
			height++;
		}
	}
}

void	while_width(t_map *map, int nb_sprite, int width, int bottom)
{
	int	size;
	int	width_left;
	int	x_sprite;

	if (map->sprite)
	{
		x_sprite = (int)floor(map->sprite[nb_sprite].x_sprite);
		size = (int)floor(map->sprite[nb_sprite].size);
		width_left = (map->res_x >> 1) + x_sprite - (size >> 1);
		if (width_left < 0)
			width_left = 0;
		while (width > width_left)
		{
			if (map->tick <= 30)
				map->sprite[nb_sprite].u = ((width_left - (map->res_x >> 1)
							- x_sprite
							+ (size >> 1)) + size) * map->image[5].width / size;
			else
				map->sprite[nb_sprite].u = ((width_left - (map->res_x >> 1)
							- x_sprite
							+ (size >> 1)) + size) * map->image[6].width / size;
			while_height(map, bottom, nb_sprite, width_left);
			width_left++;
		}
	}
}

void	sprite_mapping(t_map *map, unsigned int nb_sprite)
{
	int	bottom;
	int	width;
	int	size;

	size = 0;
	width = 0;
	if (map->sprite)
	{
		size = (int)floor(map->sprite[nb_sprite].size);
		width = (map->res_x >> 1) + (int)floor(map->sprite[nb_sprite].x_sprite)
			- (size >> 1) + size;
	}
	bottom = ((map->res_y - size) >> 1) + size;
	if (bottom > map->res_y)
		bottom = map->res_y;
	if (width > map->res_x)
		width = map->res_x;
	while_width(map, nb_sprite, width, bottom);
}

/*
 ** We need to quicksort the sprite from distance,
 ** sprites will be displayed from the nearest to the farthest.
*/

void	display_sprite(t_map *map, int square, unsigned int nb_spt)
{
	quicksort_sprite(map, map->sprite, nb_spt, square);
	while (nb_spt > 0)
	{
		nb_spt--;
		map->sprite[nb_spt].distance = map->sprite[nb_spt].distance / square;
		map->sprite[nb_spt].degree = atan2(map->sprite[nb_spt].y
				- (square * (map->player.pos_y + 1.000000)),
				map->sprite[nb_spt].x
				- (square * (map->player.pos_x + 1.000000)));
		map->sprite[nb_spt].degree = (-map->sprite[nb_spt].degree)
			- degree_to_radian(map->player.degree_raycast);
		map->sprite[nb_spt].degree
			= correct_distance(radian_to_degree(map->sprite[nb_spt].degree));
		degree_check_divide(map, nb_spt);
		map->sprite[nb_spt].degree
			= degree_to_radian(map->sprite[nb_spt].degree);
		map->sprite[nb_spt].size = ((map->res_x >> 1) / tan(0.523599))
			/ (cos(map->sprite[nb_spt].degree)
				* (map->sprite[nb_spt].distance));
		map->sprite[nb_spt].x_sprite = tan(map->sprite[nb_spt].degree)
			* ((map->res_x >> 1) / tan(0.523599));
		sprite_values_check(map, nb_spt);
		sprite_mapping(map, nb_spt);
	}
	tick_handler(map);
}
