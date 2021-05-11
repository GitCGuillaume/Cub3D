#include "../../includes/cub.h"

t_image	side_distance(t_map *map)
{
	t_image img;

	check_distance(map);
	if (map->player.ray_horizontal.distance_wall
			< map->player.ray_vertical.distance_wall)
	{
		if (map->player.degree > 0.0 && map->player.degree < 180.0)
			img = map->image[1];
		else
			img = map->image[4];
		map->player.distance_wall = map->player.ray_horizontal.distance_wall;
	}
	else
	{
		if (map->player.degree > 90.0 && map->player.degree < 270.0)
			img = map->image[2];
		else
			img = map->image[3];
		map->player.distance_wall = map->player.ray_vertical.distance_wall;
	}
	if (map->player.distance_wall < 0.0
			|| cpr_equal(map->player.distance_wall, 0.0))
		map->player.distance_wall = 0.000001;
	return (img);
}

void	math_wall(t_map *map, double correct_degree, int square_size, int x)
{
	if (map->z_buffer)
		*(map->z_buffer + x) = map->player.distance_wall;
	map->player.distance_wall =
		map->player.distance_wall * cos(degree_to_radian(correct_degree));
	map->player.slice_height = square_size
		/ map->player.distance_wall * ((map->res_x / 2) / tan(0.523599));
	map->player.height_wall = (map->res_y / 2) - (map->player.slice_height / 2);
	if (map->player.height_wall < 0)
		map->player.height_wall = 0;
	map->player.bottom_wall = (map->res_y / 2) + (map->player.slice_height / 2);
	if (map->player.bottom_wall > map->res_y)
		map->player.bottom_wall = map->res_y;
}

void	raycast_two(t_map *map, int square_size, t_image *img)
{
	if (cpr_equal(map->player.degree, 0.0)
			|| cpr_equal(map->player.degree, 90.0)
			|| cpr_equal(map->player.degree, 180.0)
			|| cpr_equal(map->player.degree, 270.0))
		map->player.degree = map->player.degree + 0.000010;
	map->player.degree = correct_distance(map->player.degree);
	horizontal_detection(map, max_lines(map), square_size);
	vertical_detection(map, max_lines(map), square_size);
	*img = side_distance(map);
}

void	raycast(t_map *map)
{
	int		x;
	int		square_size;
	double	correct_degree;
	t_image img;

	x = 0;
	square_size = map->res_x / 5;
	correct_degree = -30.0;
	map->player.degree = correct_distance(map->player.degree_raycast + 30);
	map->player.ray_horizontal.distance_wall = 0;
	map->player.ray_vertical.distance_wall = 0;
	while (map->res_x > x)
	{
		raycast_two(map, square_size, &img);
		math_wall(map, correct_degree, square_size, x);
		ceil_mapping(map, x, manage_bit_colour_ceil(map));
		texture_mapping(map, x, &img);
		floor_mapping(map, x, manage_bit_colour_floor(map));
		map->player.degree -= 60.0 / map->res_x;
		correct_degree += 60.0 / map->res_x;
		x++;
	}
	display_sprite(map, square_size, map->nb_sprite);
}
