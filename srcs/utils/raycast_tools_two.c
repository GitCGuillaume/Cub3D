/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:42:22 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:42:23 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

size_t	max_lines(t_map *map)
{
	size_t	i;

	i = 0;
	if (map->lines)
	{
		while (map->lines[i])
		{
			i++;
		}
	}
	return (i);
}

double	correct_distance(double value)
{
	if (value > 359.000000)
		value -= 360.000000;
	else if (value < 0.000000)
		value += 360.000000;
	return (value);
}
