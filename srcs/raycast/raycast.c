#include "../../includes/cub.h"

#include <stdio.h>

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
		map->player.degree_raycast = 90;
		return (1);
	}
	else if (map->player.start_position == 'S')
	{
		map->player.degree_raycast = 270;
		return (1);
	}
	else if (map->player.start_position == 'E')
	{
		map->player.degree_raycast = 0;
		return (1);
	}
	else if (map->player.start_position == 'W')
	{
		map->player.degree_raycast = 180;
		return (1);
	}
	return (0);
}

double	radian_to_degree(double radian)
{
	return (radian * 180.0 / M_PI);
}

double	degree_to_radian(double degree)
{
	return ((degree * M_PI) / 180.0);
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

void	instanciate_pos_ver(t_map *map, int square_size)
{
	map->player.ray_vertical.is_wall = 0;
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1.0);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1.0) * square_size;
	map->player.ray_vertical.pos_y -= square_size - 1.0;
	map->player.ray_vertical.pos_x -= square_size - 1.0;
}

void	instanciate_length_ver(t_map *map, double tang, int square_size)
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
}

void	vertical_check(t_map *map, double *length_case_x,
		double *length_case_y, int square)
{
	if (map->player.ray_vertical.is_wall == 1
			|| map->lines[(int)floor(*length_case_y) / square]
			[(int)floor(*length_case_x) / square] == '1'
			|| map->lines[(int)floor(*length_case_y) / square]
			[(int)floor(*length_case_x) / square] == ' ')
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

void	vertical_detection(t_map *map, int number_lines, int square_size)
{
	int		square;
	double	tang;
	double	length_case_y;
	double	length_case_x;

	square = map->res_x / 5;
	tang = tan(degree_to_radian(map->player.degree));
	if (cpr_equal(tang, 0.000000))
		tang = 0.000001;
	instanciate_pos_ver(map, square_size);
	instanciate_length_ver(map, tang, square_size);
	length_case_y = map->player.ray_vertical.length_case_y;
	length_case_x = map->player.ray_vertical.length_case_x;
	while (map->player.ray_vertical.is_wall == 0)
	{
		if (length_case_y < 0.0 || length_case_x < 0.0
				|| (int)floor(length_case_y / square) > number_lines
				|| cpr_equal((int)floor(length_case_y / square), number_lines)
				|| (length_case_x / square)
				> max_case(map->lines[(int)floor(length_case_y / square)])
				|| cpr_equal((length_case_x / square),
					max_case(map->lines[(int)floor(length_case_y / square)])))
			map->player.ray_vertical.is_wall = 1;
		vertical_check(map, &length_case_x, &length_case_y, square);
	}
}

void	instanciate_pos_hor(t_map *map, int square_size)
{
	map->player.ray_horizontal.is_wall = 0;
	map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.pos_y = square_size * (map->player.pos_y + 1.0);
	map->player.ray_horizontal.pos_x = (map->player.pos_x + 1.0) * square_size;
	map->player.ray_horizontal.pos_y -= square_size - 1.0;
	map->player.ray_horizontal.pos_x -= square_size - 1.0;
	if (map->player.ray_horizontal.distance_y <= 0)
		close_program(map, "horizontal distance y is wrong.\n", 2);
}

void	instanciate_length_hor(t_map *map, double tang, int square_size)
{
	double	floor_pos_y;

	floor_pos_y = floor(map->player.ray_horizontal.pos_y / square_size);
	if (map->player.degree > 0.0 && map->player.degree < 180.0)
		map->player.ray_horizontal.length_case_y =
			floor_pos_y
			* square_size - 0.000001;
	else
		map->player.ray_horizontal.length_case_y =
			floor_pos_y
			* square_size + square_size;
	map->player.ray_horizontal.length_case_x =
		map->player.ray_horizontal.pos_x
		+ (map->player.ray_horizontal.pos_y
				- map->player.ray_horizontal.length_case_y) / tang;
	if (map->player.degree > 0.0 && map->player.degree < 180.0)
		map->player.ray_horizontal.distance_y = -square_size;
	else
		map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.distance_x =
		-map->player.ray_horizontal.distance_y / tang;
}

void	horizontal_check(t_map *map, double *length_case_x,
		double *length_case_y, int square)
{
	if (map->player.ray_horizontal.is_wall == 1
			|| map->lines[(int)floor(*length_case_y) / square]
			[(int)floor(*length_case_x) / square] == '1'
			|| map->lines[(int)floor(*length_case_y) / square]
			[(int)floor(*length_case_x) / square] == ' ')
	{
		map->player.ray_horizontal.distance_wall =
			sqrt(pow(map->player.ray_horizontal.pos_x
						- *length_case_x, 2)
					+ pow(map->player.ray_horizontal.pos_y
						- *length_case_y, 2));
		map->player.ray_horizontal.is_wall = 1;
	}
	else
	{
		map->player.ray_horizontal.length_case_x +=
			map->player.ray_horizontal.distance_x;
		map->player.ray_horizontal.length_case_y +=
			map->player.ray_horizontal.distance_y;
		*length_case_x = map->player.ray_horizontal.length_case_x;
		*length_case_y = map->player.ray_horizontal.length_case_y;
	}
}

void	horizontal_detection(t_map *map, int number_lines, int square_size)
{
	int		square;
	double	tang;
	double	length_case_x;
	double	length_case_y;

	square = map->res_x / 5;
	tang = tan(degree_to_radian(map->player.degree));
	if (cpr_equal(tang, 0.000000))
		tang = 0.000001;
	instanciate_pos_hor(map, square_size);
	instanciate_length_hor(map, tang, square_size);
	length_case_x = map->player.ray_horizontal.length_case_x;
	length_case_y = map->player.ray_horizontal.length_case_y;
	while (map->player.ray_horizontal.is_wall == 0)
	{
		if (length_case_y < 0.0 || length_case_x < 0.0
				|| (int)floor(length_case_y) / square > number_lines
				|| cpr_equal((int)floor(length_case_y) / square, number_lines)
				|| (length_case_x / square)
				> max_case(map->lines[(int)floor(length_case_y) / square])
				|| cpr_equal((length_case_x / square),
					max_case(map->lines[(int)floor(length_case_y) / square])))
			map->player.ray_horizontal.is_wall = 1;
		horizontal_check(map, &length_case_x, &length_case_y, square);
	}
}

size_t	max_lines(t_map *map)
{
	size_t i;

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
	if (value > 359.00)
		value -= 360.0;
	else if (value < 0.0)
		value += 360.0;
	return (value);
}

int	text_map_u(t_map *map, t_image *img)
{
	double	pos_u;
	int		u;

	pos_u = 0;
	u = 0;
	if (map->player.ray_horizontal.distance_wall
			< map->player.ray_vertical.distance_wall)
	{
		pos_u = map->player.ray_horizontal.pos_y
			+ (map->player.ray_horizontal.length_case_x
					/ map->player.ray_horizontal.distance_y);
	}
	else
	{
		pos_u = map->player.ray_vertical.pos_x
			+ (map->player.ray_vertical.length_case_y
					/ map->player.ray_vertical.distance_x);
	}
	pos_u -= floor(pos_u);
	pos_u = pos_u * (double)img->width;
	u = (int)floor(pos_u);
	return (u);
}

int	text_map_v(t_map *map, int height, double zoom, t_image *img)
{
	double	pos_v;
	int		v;

	if (height >= 2147483647
			|| map->player.bottom_wall >= 2147483647 || height < 0)
		close_program(map,
				"Size window exceed the limit handled by the engine\n.", 2);
	pos_v = (height - (map->res_y / 2) + (map->player.slice_height / 2)) * zoom;
	v = (int)floor(pos_v);
	return (v);
}

void	texture_mapping(t_map *map, int x, int square, t_image *img)
{
	int		height;
	int		pixel;
	int		v;
	int		u;
	double	zoom;

	height = map->player.height_wall;
	pixel = 0;
	u = 0;
	v = 0;
	zoom = (double)img->height / map->player.slice_height;
	u = text_map_u(map, img);
	while (map->player.bottom_wall > height)
	{
		v = text_map_v(map, height, zoom, img);
		pixel = (height * map->image[0].line_bytes) + (x * 4);
		map->image[0].mlx_get_data[pixel + 0] =
			img->mlx_get_data[((v * img->line_bytes) + u * 4) + 0];
		map->image[0].mlx_get_data[pixel + 1] =
			img->mlx_get_data[((v * img->line_bytes) + u * 4) + 1];
		map->image[0].mlx_get_data[pixel + 2] =
			img->mlx_get_data[((v * img->line_bytes) + u * 4) + 2];
		height++;
	}
}

void	ceil_mapping(t_map *map, int x, int ceil_colour)
{
	int	y_pix;
	int	pixel;

	y_pix = map->player.height_wall;
	if (0 > y_pix)
	{
		y_pix = 0;
	}
	else
	{
		pixel = 0;
		while (y_pix >= 0)
		{
			pixel = (y_pix * map->image[0].line_bytes) + (x * 4);
			map->image[0].mlx_get_data[pixel + 0] = (ceil_colour) & 0xFF;
			map->image[0].mlx_get_data[pixel + 1] = (ceil_colour >> 8) & 0xFF;
			map->image[0].mlx_get_data[pixel + 2] = (ceil_colour >> 16) & 0xFF;
			y_pix--;
		}
	}
}

void	floor_mapping(t_map *map, int x, int floor_colour)
{
	int	i;
	int	pixel;

	i = map->player.bottom_wall;
	pixel = 0;
	if (map->res_y != map->player.bottom_wall)
	{
		while (map->res_y > i)
		{
			pixel = (i * map->image[0].line_bytes) + (x * 4);
			map->image[0].mlx_get_data[pixel + 0] = (floor_colour) & 0xFF;
			map->image[0].mlx_get_data[pixel + 1] = (floor_colour >> 8) & 0xFF;
			map->image[0].mlx_get_data[pixel + 2] = (floor_colour >> 16) & 0xFF;
			i++;
		}
	}
}

t_image	side_distance(t_map *map)
{
	t_image img;

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
		map->player.degree = map->player.degree + 0.000001;
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
	map->z_buffer = malloc(sizeof(double) * ((double)map->res_x));
	correct_degree = -30.0;
	map->player.degree = correct_distance(map->player.degree_raycast + 30);
	map->player.ray_horizontal.distance_wall = 0;
	map->player.ray_vertical.distance_wall = 0;
	while (map->res_x > x)
	{
		raycast_two(map, square_size, &img);
		math_wall(map, correct_degree, square_size, x);
		ceil_mapping(map, x, manage_bit_colour_ceil(map));
		texture_mapping(map, x, square_size, &img);
		floor_mapping(map, x, manage_bit_colour_floor(map));
		map->player.degree -= 60.0 / map->res_x;
		correct_degree += 60.0 / map->res_x;
		x++;
	}
	display_sprite(map, square_size);
	free(map->z_buffer);
}
