#include "../../includes/cub.h"

void	instanciate_pos_hor(t_map *map, double square_size)
{
	map->player.ray_horizontal.is_wall = 0;
	map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.pos_y = square_size * (map->player.pos_y + 1.000000);
	map->player.ray_horizontal.pos_x = (map->player.pos_x + 1.000000) * square_size;
	map->player.ray_horizontal.pos_y -= square_size - 1.000000;
	map->player.ray_horizontal.pos_x -= square_size - 1.000000;
	if (map->player.ray_horizontal.distance_y <= 0.000000)
		close_program(map, "horizontal distance y is wrong.\n", 2);
	if (map->player.ray_horizontal.pos_x < 0.000000
		|| map->player.ray_horizontal.pos_y < 0.000000)
	{
		close_program(map, "player position is wrong.\n", 2);
	}
}

void	instanciate_length_hor(t_map *map, double tang, double square_size)
{
	double	floor_pos_y;

	floor_pos_y = floor(map->player.ray_horizontal.pos_y / square_size);
	if (map->player.degree > 0.000000 && map->player.degree < 180.000000)
		map->player.ray_horizontal.length_case_y
			= floor_pos_y * square_size - 0.000001;
	else
		map->player.ray_horizontal.length_case_y
			= floor_pos_y * square_size + square_size;
	map->player.ray_horizontal.length_case_x = map->player.ray_horizontal.pos_x
		+ (map->player.ray_horizontal.pos_y
			- map->player.ray_horizontal.length_case_y) / tang;
	if (map->player.degree > 0.000000 && map->player.degree < 180.000000)
		map->player.ray_horizontal.distance_y = -square_size;
	else
		map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.distance_x
		= -map->player.ray_horizontal.distance_y / tang;
	check_error_ln_hor(map, floor_pos_y);
}

void	horizontal_check(t_map *map, double *length_case_x,
		double *length_case_y, double square)
{
	if (map->lines == NULL)
		close_program(map, "The engine couldn't read the map.\n", 2);
	check_loop_cast_hor(map);
	if (map->player.ray_horizontal.is_wall == 1
		|| map->lines[(int)floor(*length_case_y) / (int)square]
		[(int)floor(*length_case_x) / (int)square] == '1'
		|| map->lines[(int)floor(*length_case_y) / (int)square]
		[(int)floor(*length_case_x) / (int)square] == ' ')
	{
		map->player.ray_horizontal.distance_wall
			= sqrt(pow(map->player.ray_horizontal.pos_x
					- *length_case_x, 2.000000)
				+ pow(map->player.ray_horizontal.pos_y
					- *length_case_y, 2.000000));
		map->player.ray_horizontal.is_wall = 1;
	}
	else
	{
		map->player.ray_horizontal.length_case_x
			+= map->player.ray_horizontal.distance_x;
		map->player.ray_horizontal.length_case_y
			+= map->player.ray_horizontal.distance_y;
		*length_case_x = map->player.ray_horizontal.length_case_x;
		*length_case_y = map->player.ray_horizontal.length_case_y;
	}
}

void	horizontal_detection(t_map *map, int number_lines, double square_size)
{
	double	tang;
	double	length_case_x;
	double	length_case_y;

	tang = tan(degree_to_radian(map->player.degree));
	if (cpr_equal(tang, 0.000000))
		tang = 0.000001;
	instanciate_pos_hor(map, square_size);
	instanciate_length_hor(map, tang, square_size);
	length_case_x = map->player.ray_horizontal.length_case_x;
	length_case_y = map->player.ray_horizontal.length_case_y;
	while (map->lines && map->player.ray_horizontal.is_wall == 0)
	{
		if (length_case_y < 0.000000 || length_case_x < 0.000000
			|| (int)floor(length_case_y) / square_size > number_lines
			|| cpr_equal((int)floor(length_case_y) / square_size, number_lines)
			|| (length_case_x / square_size)
			> max_case(map->lines[(int)floor(length_case_y) / (int)square_size])
			|| cpr_equal((length_case_x / square_size),
				max_case(map->lines[(int)floor(length_case_y) / (int)square_size])))
			map->player.ray_horizontal.is_wall = 1;
		horizontal_check(map, &length_case_x, &length_case_y, square_size);
	}
}
