#include "../../includes/cub.h"

void	check_error_ln_hor(t_map *map, double floor_pos_y)
{
	if ((floor_pos_y <= -2147483647.000000 || floor_pos_y >= 2147483647.000000)
			|| (map->player.ray_horizontal.length_case_x <= -2147483647.000000
				|| map->player.ray_horizontal.length_case_x >= 2147483647.000000)
		|| (map->player.ray_horizontal.length_case_y <= -2147483647.000000
				|| map->player.ray_horizontal.length_case_y >= 2147483647.000000))
	{
		close_program(map, "horizontal ray casting is wrong.\n", 2);
	}
}

void	check_error_ln_ver(t_map *map, double floor_pos_x)
{
	if ((floor_pos_x <= -2147483647.000000 || floor_pos_x >= 2147483647.000000)
			|| (map->player.ray_vertical.length_case_x <= -2147483647.000000
				|| map->player.ray_vertical.length_case_x >= 2147483647.000000)
		|| (map->player.ray_vertical.length_case_y <= -2147483647.000000
				|| map->player.ray_vertical.length_case_y >= 2147483647.000000))
	{
		close_program(map, "vertical ray casting is wrong.\n", 2);
	}
}

void	check_loop_cast_hor(t_map *map)
{
	if (map->player.ray_horizontal.length_case_x >= 2147483647.000000
		|| map->player.ray_horizontal.length_case_y >= 2147483647.000000)
	{
		close_program(map,
				"horizontal ray casting values loop are wrong.\n", 2);
	}
}

void	check_loop_cast_ver(t_map *map)
{
	if (map->player.ray_vertical.length_case_x >= 2147483647.000000
		|| map->player.ray_vertical.length_case_y >= 2147483647.000000)
	{
		close_program(map, "vertical ray casting values loop are wrong.\n", 2);
	}
}

void	check_distance(t_map *map)
{
	if (map->player.ray_horizontal.distance_wall > 2147483646.000000
			|| map->player.ray_vertical.distance_wall > 2147483646.000000)
	{
		close_program(map, "distances values are wrong.\n", 2);
	}
}
