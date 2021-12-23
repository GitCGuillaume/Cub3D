#include "../../includes/cub.h"

void	instanciate_pos_ver(t_map *map, double square_size)
{
	map->player.ray_vertical.is_wall = 0;
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1.0);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1.0) * square_size;
	map->player.ray_vertical.pos_y -= square_size - 1.0;
	map->player.ray_vertical.pos_x -= square_size - 1.0;
	if (map->player.ray_vertical.pos_x < 0
			|| map->player.ray_vertical.pos_y < 0)
	{
		close_program(map, "player position is wrong.\n", 2);
	}
}

void	instanciate_length_ver(t_map *map, double tang, double square_size)
{
	double	floor_pos_x;

	floor_pos_x = floor(map->player.ray_vertical.pos_x / square_size);
	if (map->player.degree > 90.0 && map->player.degree < 270.0)
		map->player.ray_vertical.length_case_x =
			floor_pos_x * square_size - 0.000001;
	else
		map->player.ray_vertical.length_case_x =
			floor_pos_x * square_size + square_size;
	map->player.ray_vertical.length_case_y =
		map->player.ray_vertical.pos_y
		+ (map->player.ray_vertical.pos_x
				- map->player.ray_vertical.length_case_x)
		* tang;
	if (map->player.degree > 90.0 && map->player.degree < 270.0)
		map->player.ray_vertical.distance_x = -square_size;
	else
		map->player.ray_vertical.distance_x = square_size;
	map->player.ray_vertical.distance_y =
		map->player.ray_vertical.distance_x * tang;
	map->player.ray_vertical.distance_y =
		-map->player.ray_vertical.distance_y;
	check_error_ln_ver(map, floor_pos_x);
}

void	vertical_check(t_map *map, double *length_case_x,
		double *length_case_y, double square)
{
	if (map->lines == NULL)
		close_program(map, "The engine couldn't read the map.", 2);
	check_loop_cast_ver(map);
	if (map->player.ray_vertical.is_wall == 1
			|| map->lines[(int)floor(*length_case_y) / (int)square]
			[(int)floor(*length_case_x) / (int)square] == '1'
			|| map->lines[(int)floor(*length_case_y) / (int)square]
			[(int)floor(*length_case_x) / (int)square] == ' ')
	{
		map->player.ray_vertical.distance_wall =
			sqrt(pow(map->player.ray_vertical.pos_x
						- *length_case_x, 2)
				+ pow(map->player.ray_vertical.pos_y
					- *length_case_y, 2));
		map->player.ray_vertical.is_wall = 1;
	}
	else
	{
		map->player.ray_vertical.length_case_x +=
			map->player.ray_vertical.distance_x;
		map->player.ray_vertical.length_case_y +=
			map->player.ray_vertical.distance_y;
		*length_case_x = map->player.ray_vertical.length_case_x;
		*length_case_y = map->player.ray_vertical.length_case_y;
	}
}

void	vertical_detection(t_map *map, int number_lines, double square_size)
{
	double	tang;
	double	length_case_y;
	double	length_case_x;

	tang = tan(degree_to_radian(map->player.degree));
	if (cpr_equal(tang, 0.0))
		tang = tang + 0.000010;
	instanciate_pos_ver(map, square_size);
	instanciate_length_ver(map, tang, square_size);
	length_case_y = map->player.ray_vertical.length_case_y;
	length_case_x = map->player.ray_vertical.length_case_x;
	while (map->lines && map->player.ray_vertical.is_wall == 0)
	{
		if (length_case_y < 0.0 || length_case_x < 0.0
				|| (int)floor(length_case_y) / square_size > number_lines
				|| cpr_equal((int)floor(length_case_y) / square_size, number_lines)
				|| (length_case_x / square_size)
				> max_case(map->lines[(int)floor(length_case_y) / (int)square_size])
				|| cpr_equal((length_case_x / square_size),
					max_case(map->lines[(int)floor(length_case_y) / (int)square_size])))
			map->player.ray_vertical.is_wall = 1;
		vertical_check(map, &length_case_x, &length_case_y, square_size);
	}
}
