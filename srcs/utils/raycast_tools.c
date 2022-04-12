/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:42:28 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:42:29 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	cpr_equal(double a, double b)
{
	if (fabs(a - b) < 0.000001)
		return (1);
	else
		return (0);
	return (0);
}

int	start_ray_direction(t_map *map)
{
	if (map->player.start_position == 'N')
	{
		map->player.degree_raycast = 90.000000;
		return (1);
	}
	else if (map->player.start_position == 'S')
	{
		map->player.degree_raycast = 270.000000;
		return (1);
	}
	else if (map->player.start_position == 'E')
	{
		map->player.degree_raycast = 0.000000;
		return (1);
	}
	else if (map->player.start_position == 'W')
	{
		map->player.degree_raycast = 180.000000;
		return (1);
	}
	return (0);
}

double	radian_to_degree(double radian)
{
	return (radian * 180.000000 / PI);
}

double	degree_to_radian(double degree)
{
	return ((degree * PI) / 180.000000);
}

double	max_case(char *line)
{
	double	i;

	i = 0.0;
	if (line != NULL)
	{
		while (line[(int)i] != '\0')
		{
			i++;
		}
	}
	return (i);
}
