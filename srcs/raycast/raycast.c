#include "../../includes/cub.h"

t_image	*side_distance(t_map *map)
{
	t_image	*img;

	img = NULL;
	if (map->player.ray_horizontal.distance_wall
		< map->player.ray_vertical.distance_wall)
	{
		if (map->player.degree > 0.000000 && map->player.degree < 180.000000)
			img = &map->image[1];
		else
			img = &map->image[4];
		map->player.distance_wall = map->player.ray_horizontal.distance_wall;
	}
	else
	{
		if (map->player.degree > 90.000000 && map->player.degree < 270.000000)
			img = &map->image[2];
		else
			img = &map->image[3];
		map->player.distance_wall = map->player.ray_vertical.distance_wall;
	}
	if (map->player.distance_wall < 0.000000
		|| cpr_equal(map->player.distance_wall, 0.000000))
		map->player.distance_wall = 0.000001;
	return (img);
}

void	math_wall(t_map *map, double correct_degree, double square_size)
{
	map->player.distance_wall
		= map->player.distance_wall * cos(degree_to_radian(correct_degree));
	map->player.slice_height = square_size
		/ map->player.distance_wall * ((map->res_x >> 1) / tan(0.523599));
	map->player.height_wall
		= (map->res_y >> 1) - (map->player.slice_height >> 1);
	if (map->player.height_wall < 0)
		map->player.height_wall = 0;
	map->player.bottom_wall
		= (map->res_y >> 1) + (map->player.slice_height >> 1);
	if (map->player.bottom_wall > map->res_y)
		map->player.bottom_wall = map->res_y;
}

void	raycast_two(t_map *map, double square_size)
{
	if (cpr_equal(map->player.degree, 0.000000)
		|| cpr_equal(map->player.degree, 90.000000)
		|| cpr_equal(map->player.degree, 180.000000)
		|| cpr_equal(map->player.degree, 270.000000))
		map->player.degree = map->player.degree + 0.000010;
	map->player.degree = correct_distance(map->player.degree);
	horizontal_detection(map, max_lines(map), square_size);
	vertical_detection(map, max_lines(map), square_size);
	map->img = side_distance(map);
}

void	raycast(t_map *map)
{
	double	square_size;
	double	correct_degree;
	int		x;

	square_size = floor((double)map->res_x) / 5.000000;
	x = 0;
	if ((int)floor(square_size) == 0)
		square_size = 1.000000;
	correct_degree = -30.000000;
	map->player.degree
		= correct_distance(map->player.degree_raycast + 30.000000);
	map->player.ray_horizontal.distance_wall = 0.000000;
	map->player.ray_vertical.distance_wall = 0.000000;
	while (map->res_x > x)
	{
		raycast_two(map, square_size);
		math_wall(map, correct_degree, square_size);
		ceil_mapping(map, x, manage_bit_colour_ceil(map));
		texture_mapping(map, x);
		floor_mapping(map, x, manage_bit_colour_floor(map));
		map->player.degree -= 60.000000 / map->res_x;
		correct_degree += 60.000000 / map->res_x;
		x++;
	}
	map->img = NULL;
}
