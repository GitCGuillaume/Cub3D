/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:48:21 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 10:53:22 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	>> 3 == / 8
*/

void	texture_mapping_two(t_map *map, int v, int u, int pixel)
{
	if (map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 0])
		map->image[0].mlx_get_data[pixel + 0]
			= map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 0];
	if (map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 1])
		map->image[0].mlx_get_data[pixel + 1]
			= map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 1];
	if (map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 2])
		map->image[0].mlx_get_data[pixel + 2]
			= map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 2];
	if (map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 3])
		map->image[0].mlx_get_data[pixel + 3]
			= map->img->mlx_get_data[((v * map->img->line_bytes)
				+ u * (map->image[0].bpp >> 3)) + 3];
}
