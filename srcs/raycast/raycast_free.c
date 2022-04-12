/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:40:10 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:40:28 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	check_distance(t_map *map)
{
	if (map->player.ray_horizontal.distance_wall > 2147483646.000000
		|| map->player.ray_vertical.distance_wall > 2147483646.000000)
	{
		close_program(map, "distances values are wrong.\n", 2);
	}
}
