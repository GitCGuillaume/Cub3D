#include "../../includes/cub.h"

#include <stdio.h>

int	compare_equal(double a, double b)
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

double	degree_to_radian(double degree)
{
	return ((degree * M_PI)/180.0);
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

void	vertical_detection(t_map *map, int number_lines)
{
	/** height grill and x intersection between 2 cases**/
	double	radian;
	int	square_size;
	int square = map->res_x / 5;

	square_size = map->res_x / 5;
	radian = tan(degree_to_radian(map->player.degree));
	if (fabs(radian - 0.000000) < 0.000001)
	{
		radian = 0.000001;
	}
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1.0);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1.0) * square_size;
	map->player.ray_vertical.pos_y -= square_size - 1.0;
	map->player.ray_vertical.pos_x -= square_size - 1.0;
	/** GET HIGHEST Y side of the case from current position **/
	if (map->player.degree < 90.0 || map->player.degree > 270.0)
		map->player.ray_vertical.length_case_x = floor(map->player.ray_vertical.pos_x / square_size) * square_size + square_size;
	else
		map->player.ray_vertical.length_case_x = floor(map->player.ray_vertical.pos_x / square_size) * square_size - 0.000001;
	map->player.ray_vertical.length_case_y = map->player.ray_vertical.pos_y
		+ (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x) * radian;
	//FIND XA
	if (map->player.degree < 90.0 || map->player.degree > 270.0)
		map->player.ray_vertical.distance_x = square_size;
	else
		map->player.ray_vertical.distance_x = -square_size;
	//FIND YA
	map->player.ray_vertical.distance_y = map->player.ray_vertical.distance_x * radian;
	map->player.ray_vertical.distance_y = -map->player.ray_vertical.distance_y;
	map->player.ray_vertical.is_wall = 0;
	//if (map->player.ray_vertical.length_case_x < 0.0
	//			|| (map->player.ray_vertical.length_case_x / square) 
	//			>= max_case(map->lines[(int)floor(floor(map->player.ray_vertical.length_case_y) / square)]))
	//	{
	while (map->player.ray_vertical.is_wall == 0)
	{
		if (map->player.ray_vertical.length_case_y < 0.0
				|| map->player.ray_vertical.length_case_x < 0.0
				|| (int)floor(map->player.ray_vertical.length_case_y / square)
				> number_lines
				|| compare_equal((int)floor(map->player.ray_vertical.length_case_y / square), number_lines)
				|| (map->player.ray_vertical.length_case_x / square)
				> max_case(map->lines[(int)map->player.ray_vertical.length_case_y / square])
				|| compare_equal((map->player.ray_vertical.length_case_x / square), max_case(map->lines[(int)map->player.ray_vertical.length_case_y / square])))
		{
			//map->player.ray_vertical.length_case_y += map->player.ray_vertical.distance_y;
			map->player.ray_vertical.is_wall = 1;
			//map->player.ray_vertical.length_case_x += map->player.ray_vertical.distance_x;
			
			map->player.ray_vertical.is_wall = 1;
		}
		if (map->player.ray_vertical.is_wall == 1 || map->lines[(int)floor(map->player.ray_vertical.length_case_y) / square][(int)floor(map->player.ray_vertical.length_case_x) / square] == '1')
		{
			//map->player.ray_vertical.distance_wall = sqrt(pow(map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x, 2)
			//		+ pow(map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y, 2));
			map->player.ray_vertical.distance_wall = sqrt(((map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
				* (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x))
				+ ((map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)
				* (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)));
			map->player.ray_vertical.is_wall = 1;
		}
		else
		{
			map->player.ray_vertical.length_case_x += map->player.ray_vertical.distance_x;
			map->player.ray_vertical.length_case_y += map->player.ray_vertical.distance_y;
		}
	}
}


void	horizontal_detection(t_map *map, int number_lines)
{
	/** height grill and x intersection between 2 cases**/
	double	radian;
	int	square_size;
	int square = map->res_x / 5;

	square_size = map->res_x / 5;
	radian = tan(degree_to_radian(map->player.degree));
	/*if (fabs(radian - 0.000000) < 0.000001)
	{
		radian = 0.000001;
	}*/
	map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.pos_y = square_size * (map->player.pos_y + 1.0);
	map->player.ray_horizontal.pos_x = (map->player.pos_x + 1.0) * square_size;
	map->player.ray_horizontal.pos_y -= square_size - 1.0;
	map->player.ray_horizontal.pos_x -= square_size - 1.0;
	/** GET HIGHEST Y side of the case from current position **/
	if (map->player.degree > 0.0 && map->player.degree < 180.0)
		map->player.ray_horizontal.length_case_y = floor(map->player.ray_horizontal.pos_y / square_size) * square_size - 0.000001;
	else
		map->player.ray_horizontal.length_case_y = floor(map->player.ray_horizontal.pos_y / square_size) * square_size + square_size;
	map->player.ray_horizontal.length_case_x = map->player.ray_horizontal.pos_x
		+ (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y) / radian;
	//FIND YA
	if (map->player.degree > 0.0 && map->player.degree < 180.0)
		map->player.ray_horizontal.distance_y = -square_size;
	else
		map->player.ray_horizontal.distance_y = square_size;
	//FIND XA
	map->player.ray_horizontal.distance_x = -map->player.ray_horizontal.distance_y / radian;
	map->player.ray_horizontal.is_wall = 0;
	while (map->player.ray_horizontal.is_wall == 0)
	{
		//printf("i horizontal = %d", i);
		
		//if (floor(map->player.ray_horizontal.length_case_y / square) >= number_lines)
		//	map->player.ray_horizontal.length_case_y = (number_lines) * square;
		//printf("y_case_horizontal=%d\n", (int)floor(map->player.ray_horizontal.length_case_y / square));
		//if (map->player.ray_horizontal.length_case_y < 0.0)
		//		map->player.ray_horizontal.length_case_y = 0.0;
		/*if (map->player.ray_horizontal.length_case_y < 0.0
				|| map->player.ray_horizontal.length_case_x < 0.0
				|| (int)floor(floor(map->player.ray_horizontal.length_case_y) / square)
				> number_lines
				|| (map->player.ray_horizontal.length_case_x / square)
				> max_case(map->lines[(int)floor(floor(map->player.ray_horizontal.length_case_y) / square)]))
		{
			//map->player.ray_horizontal.distance_wall = 9999999.0;
			map->player.ray_horizontal.length_case_x += map->player.ray_horizontal.distance_x;
			map->player.ray_horizontal.length_case_y += map->player.ray_horizontal.distance_y;
			map->player.ray_horizontal.is_wall = 1;
			break;
		}*/
		//if (map->player.ray_horizontal.length_case_x < 0.0
		//		|| (map->player.ray_horizontal.length_case_x / square)
		//		> max_case(map->lines[(int)floor(floor(map->player.ray_horizontal.length_case_y) / square)]))
		//{
		if (map->player.ray_horizontal.length_case_y < 0.0
				|| map->player.ray_horizontal.length_case_x < 0.0
				|| (int)map->player.ray_horizontal.length_case_y / square
				> number_lines
				|| compare_equal((int)map->player.ray_horizontal.length_case_y / square, number_lines)
				|| (map->player.ray_horizontal.length_case_x / square)
				> max_case(map->lines[(int)map->player.ray_horizontal.length_case_y / square])
				|| compare_equal((map->player.ray_horizontal.length_case_x / square), max_case(map->lines[(int)map->player.ray_horizontal.length_case_y / square])))
		{
			//map->player.ray_horizontal.length_case_y += map->player.ray_horizontal.distance_y;
			//map->player.ray_horizontal.length_case_x += map->player.ray_horizontal.distance_x;
			map->player.ray_horizontal.is_wall = 1;
		}
		if (map->player.ray_horizontal.is_wall == 1 || map->lines[(int)floor(map->player.ray_horizontal.length_case_y) / square][(int)floor(map->player.ray_horizontal.length_case_x) / square] == '1')
		{
			//map->player.ray_horizontal.distance_wall = sqrt(pow(map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x, 2)
			//		+ pow(map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y, 2));
			map->player.ray_horizontal.distance_wall = sqrt(((map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
				* (map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x))
				+ ((map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)
				* (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)));
			map->player.ray_horizontal.is_wall = 1;
		}
		else
		{
			map->player.ray_horizontal.length_case_x += map->player.ray_horizontal.distance_x;
			map->player.ray_horizontal.length_case_y += map->player.ray_horizontal.distance_y;
		}
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
	if (value > 360.0)
		value -= 360.0;
	else if (value < 0.0)
		value += 360.0;
	return (value);
}

void	texture_mapping(t_map *map, double pos_u, int x, int square)
{
double	pos_v;
double	zoom;
int y = 0;
double distance = 0;
	int	i;
	int	max;
	int	pixel;
	i = map->player.height_wall;
	max = map->player.bottom_wall;
	pixel = 0;
	pos_v = 0;
	//point relatif dans la texture + 1.0 pour  scale
	zoom =  (double)map->image[1].height / map->player.slice_height;
	//pos_v = (i - map->res_y/ 2 + map->player.slice_height / 2) * zoom; /*+ (map->image[1].height - 1);*/
	//pos_v = (map->player.bottom_wall) * zoom;
	//On obtient le milieu du mur et on va vers le haut de l'écran
	//pos_v = (i - ) * zoom;
	//On obtient la position du rayon sur la carte,et on réduit la position pour obtenir la position du rayon dans la texture en x (ex:1..5-1=0.5)
	double length=0;
	if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall)
	{
		pos_u=0;
		//length = map->player.ray_horizontal.distance_x;
		distance = map->player.ray_horizontal.distance_y;
		pos_u = map->player.ray_horizontal.pos_y + (map->player.offset_tex / map->player.ray_horizontal.distance_y);
		pos_u -= floor(pos_u);
		pos_u = pos_u * 64.0;
		if (map->player.ray_horizontal.distance_x > 0)
			pos_u = 64.0 - ceil(pos_u) - 1;
	}
	else
	{
		length = map->player.ray_vertical.length_case_x;
		distance = map->player.ray_vertical.distance_x;
		pos_u = map->player.ray_vertical.pos_x + (map->player.offset_tex / map->player.ray_vertical.distance_x);
		pos_u -= floor(pos_u);
		pos_u = pos_u * 64.0;
		if (map->player.ray_vertical.distance_y < 0)
			pos_u = 64.0 - ceil(pos_u) - 1;
	}
	pos_u -= 1;
	//pos_u = map->player.offset_tex * (distance / (length));
	//printf("pos_u=%f, off=%d", pos_u, (int)map->player.offset_tex%64);exit(0);
	if (i >= 2147483647 || max >= 2147483647 || i < 0)
		close_program(map, "Size window exceed the limit pixel handled by the engine\n.", 2);
	while (max > i)
	{
		pos_v = ((i - (map->res_y / 2) + (map->player.slice_height / 2))) * zoom;
		pos_v += zoom;
		y = pos_v - 1;
		//y = (int)(pos_v) * (map->image[1].height - 1);
		pixel = (i * map->image[0].line_bytes) + (x * 4);
		map->image[0].mlx_get_data[pixel + 0]
			= map->image[1].mlx_get_data[((y * map->image[1].line_bytes) + ((int)(pos_u))*4) + 0];
		map->image[0].mlx_get_data[pixel + 1]
			= map->image[1].mlx_get_data[((y * map->image[1].line_bytes) + ((int)(pos_u))*4) + 1];
		map->image[0].mlx_get_data[pixel + 2]
			= map->image[1].mlx_get_data[((y * map->image[1].line_bytes) + ((int)(pos_u))*4) + 2];
		map->image[0].mlx_get_data[pixel + 3]
			= map->image[1].mlx_get_data[((y * map->image[1].line_bytes) + ((int)(pos_u))*4) + 3];
		i++;
	}
}

void	raycast(t_map *map)
{
	int	x;
	double	fisheye;
	int	slice_height;
	int	square_size;
	double	add_degree;
	double	correct_degree;
	size_t	number_lines;
int side = 0;
	map->player.degree = correct_distance(map->player.degree_raycast + 30);
	square_size = map->res_x / 5;
	number_lines = max_lines(map);
	x = 0;
	add_degree = 60.0 / map->res_x;
	correct_degree = -30.0;
	map->player.ray_horizontal.distance_wall = 0;
	map->player.ray_vertical.distance_wall = 0;
	while (map->res_x > x)
	{
		if (compare_equal(map->player.degree, 0.0) || compare_equal(map->player.degree, 90.0)
				|| compare_equal(map->player.degree, 180.0) || compare_equal(map->player.degree, 270.0))
		{
			map->player.degree = map->player.degree + 0.000001;
		}
		map->player.degree = correct_distance(map->player.degree);
		horizontal_detection(map, number_lines);
		vertical_detection(map, number_lines);
		//if (compare_equal(map->player.ray_horizontal.distance_wall, 0.0))
		//{
			//map->player.ray_horizontal.distance_wall = sqrt(pow(map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x, 2)
			//		+ pow(map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y, 2));
		//}
		//if (compare_equal(map->player.ray_vertical.distance_wall, 0.0))
		//{
			//map->player.ray_vertical.distance_wall = sqrt(pow(map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x, 2)
			//		+ pow(map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y, 2));
		//}
		/*map->player.ray_horizontal.distance_wall = sqrt(((map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
				* (map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x))
				+ ((map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)
				* (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)));
		map->player.ray_vertical.distance_wall = sqrt(((map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
				* (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x))
				+ ((map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)
				* (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)));
		*/
		double pos_u = 0;
		if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall)
		{
			map->player.distance_wall = map->player.ray_horizontal.distance_wall;
			map->player.offset_tex = map->player.ray_horizontal.length_case_x;
		}
		else
		{
			map->player.distance_wall = map->player.ray_vertical.distance_wall;
			map->player.offset_tex = map->player.ray_vertical.length_case_y;
		}
		if (map->player.distance_wall < 0.0 || compare_equal(map->player.distance_wall, 0.0))
			map->player.distance_wall = 0.000001;
		map->player.distance_wall = map->player.distance_wall * cos(degree_to_radian(correct_degree));
		//map->player.slice_height = square_size * ((map->res_x / 2) / tan(0.523599)) / map->player.distance_wall;
		map->player.slice_height = square_size / map->player.distance_wall * ((map->res_x / 2) / tan(0.523599));
		map->player.height_wall = (map->res_y / 2) - (map->player.slice_height / 2);
		if (map->player.height_wall < 0)
			map->player.height_wall = 0;
		map->player.bottom_wall = (map->res_y / 2) + (map->player.slice_height /2);
		if (map->player.bottom_wall > map->res_y)
				map->player.bottom_wall = map->res_y-1;
		//map->player.height_wall = map->res_y - map->player.bottom_wall;
		//put_pixel(map, x, map->image[0].line_bytes, map->image[0].bpp, manage_bit_colour_ceiling(map));
		texture_mapping(map, pos_u, x, square_size);
		map->player.degree -= add_degree;
		correct_degree += add_degree;
		x++;
	}
}
