/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_map_three.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:02:31 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/12 14:09:30 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	flood_fill_2(t_map *map, int x, int y, char old_value)
{
	if (map->lines_copy)
	{
		if (map->lines_copy[y - 1][x - 1] != '1'
				&& map->lines_copy[y - 1][x - 1] != ' ')
			flood_fill(map, x - 1, y - 1, old_value);
		if (map->lines_copy[y][x + 1] != '1'
				&& map->lines_copy[y][x + 1] != ' ')
			flood_fill(map, x + 1, y, old_value);
		if (map->lines_copy[y][x - 1] != '1'
				&& map->lines_copy[y][x - 1] != ' ')
			flood_fill(map, x - 1, y, old_value);
	}
}
