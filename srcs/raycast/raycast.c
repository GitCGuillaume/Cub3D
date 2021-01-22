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
		if (map->player.ray_vertical.is_wall == 1 || map->lines[(int)floor(map->player.ray_vertical.length_case_y) / square][(int)floor(map->player.ray_vertical.length_case_x) / square] == '1' || map->lines[(int)floor(map->player.ray_vertical.length_case_y) / square][(int)floor(map->player.ray_vertical.length_case_x) / square] == ' ')
		{
			map->player.ray_vertical.distance_wall = sqrt(pow(map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x, 2)
					+ pow(map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y, 2));
			/*map->player.ray_vertical.distance_wall = sqrt(((map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
				* (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x))
				+ ((map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)
				* (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)));
			*/
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
		if (map->player.ray_horizontal.is_wall == 1 || map->lines[(int)floor(map->player.ray_horizontal.length_case_y) / square][(int)floor(map->player.ray_horizontal.length_case_x) / square] == '1'
				|| map->lines[(int)floor(map->player.ray_horizontal.length_case_y) / square][(int)floor(map->player.ray_horizontal.length_case_x) / square] == ' ')
		{
			map->player.ray_horizontal.distance_wall = sqrt(pow(map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x, 2)
					+ pow(map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y, 2));
			/*map->player.ray_horizontal.distance_wall = sqrt(((map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
				* (map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x))
				+ ((map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)
				* (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)));
			*/
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
	if (value > 359.00)
		value -= 360.0;
	else if (value < 0.0)
		value += 360.0;
	return (value);
}

void	texture_mapping(t_map *map, double pos_u, int x, int square, t_image *test)
{
double	pos_v;
double	zoom;
int y = 0;
double distance = 0;
	int	i;
	int	max;
	int	pixel;

	i = floor(map->player.height_wall);
	max = floor(map->player.bottom_wall);
	pixel = 0;
	pos_v = 0;
	//On obtient le milieu du mur et on va vers le haut de l'écran
	zoom = ((double)test->height / map->player.slice_height);
	//On obtient la position du rayon sur la carte,et on réduit la position pour obtenir la position du rayon dans la texture en x (ex:1..5-1=0.5)
	double length=0;
	if (i >= 2147483647 || max >= 2147483647 || i < 0)
		close_program(map, "Size window exceed the limit pixel handled by the engine\n.", 2);
	if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall)
	{
		//length = map->player.ray_horizontal.distance_x;
		distance = map->player.ray_horizontal.distance_y;
		pos_u = map->player.ray_horizontal.pos_y + (map->player.ray_horizontal.length_case_x / map->player.ray_horizontal.distance_y);
	}
	else
	{
		length = map->player.ray_vertical.length_case_x;
		distance = map->player.ray_vertical.distance_x;
		pos_u = map->player.ray_vertical.pos_x + (map->player.ray_vertical.length_case_y / map->player.ray_vertical.distance_x);
	}
	pos_u -= floor(pos_u);
	pos_u = pos_u * 64.0;
		/*if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall && map->player.ray_horizontal.distance_x > 0)
		{
			pos_u = 64.0 - ceil(pos_u);
		}

		if (map->player.ray_horizontal.distance_wall > map->player.ray_vertical.distance_wall && map->player.ray_vertical.distance_y < 0)
		*/
	//pos_u = 64.0 - pos_u;
	//pos_u *= 1.0;
	while (max > i)
	{
		pos_v = ((i - (map->res_y / 2) + (map->player.slice_height / 2))) * zoom;
		// -1 sinon texture pas complète
		y = (int)floor(pos_v);
		//y = (int)pos_v; //& (test->height - 1);
		pixel = (i * map->image[0].line_bytes) + (x * 4);
		map->image[0].mlx_get_data[pixel + 0]
			= test->mlx_get_data[((y * test->line_bytes) + ((int)(pos_u))*4) + 0];
		map->image[0].mlx_get_data[pixel + 1]
			= test->mlx_get_data[((y * test->line_bytes) + ((int)(pos_u))*4) + 1];
		map->image[0].mlx_get_data[pixel + 2]
			= test->mlx_get_data[((y * test->line_bytes) + ((int)(pos_u))*4) + 2];
		map->image[0].mlx_get_data[pixel + 3]
			= test->mlx_get_data[((y * test->line_bytes) + ((int)(pos_u))*4) + 3];
		i++;
	}
}

void	sprite_mapping(t_map *map, unsigned int nb_sprite)
{
	int	i;
	int	pixel;
	int	width_left;
	int	width_right;
	int	height;
	int	bottom;
	int	width;
	int	u;
	i = 0;
	pixel = 0;
	//size = 64.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599));
	//width_left = 64.0 / sqrt(pow((64 * (map->player.pos_x + 1.0)) - (double)map->sprite[0].x, 2)) * ((map->res_x / 2) / tan(0.523599));
	//width_left = (map->res_x / 2) - sqrt(pow((64 * (map->player.pos_x + 1.0)) - (double)map->sprite[0].x, 2)) / 2;
	//width_left = map->sprite[0].x_sprite - width_left;
	//width_right = map->sprite[0].x_sprite + (64.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599))) / 2.0;
	
	//width_right = map->sprite[0].x_sprite + sqrt(pow((64 * (map->player.pos_x + 1.0)) - (double)map->sprite[0].x, 2)) / 2;
	width_left = (map->res_x / 2) + map->sprite[nb_sprite].x_sprite - ((int)map->sprite[nb_sprite].size / 2);
	//width_right = (map->res_x / 2) + map->sprite[0].x_sprite - ((int)map->sprite[0].size / 2);
	//width_right = (map->res_x / 2) + map->sprite[0].x_sprite + (size / 2);
	//width_left = (map->res_x / 2) + map->sprite[0].x_sprite - (size / 2);
	//width = map->sprite[0].distance;
	//height = (map->res_y / 2) - (32.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599))) / 2.0;
	//bottom = (map->res_y / 2) + (64.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599))) / 2.0;
	//bottom = (map->res_y / 2) + (32.0 map->sprite[0].distance;
	
	//map->player.slice_height = square_size / map->player.distance_wall * ((map->res_x / 2) / tan(0.523599));
	//bottom = 64.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599));
	width = width_left + (int)map->sprite[nb_sprite].size;
	//width = (map->res_x / 2) + map->sprite[0].x_sprite + ((int)map->sprite[0].size / 2);
	height = (map->res_y - map->sprite[nb_sprite].size) / 2;
	bottom = height + (int)map->sprite[nb_sprite].size;
	if (height < 0)
		height = 0;
	if (bottom > map->res_y)
		bottom = map->res_y;
	if (width_left < 0)
		width_left = 0;
	if (width > map->res_x)
		width = map->res_x;
	//if (width_right > map->res_x)
	//	width_right = map->res_x;
	//if (map->sprite[0].x_sprite > 0.0 && map->sprite[0].x_sprite < map->res_x + 1)
	//{
	u = (int)map->sprite[nb_sprite].x_sprite * (64 / (int)map->sprite[nb_sprite].distance);
	while (width > width_left) // * ((map->res_x / 2) / tan(0.523599)))/2.0 > width)
	{
		//height = 64.0 / map->sprite[0].distance * ((map->res_x / 2) / tan(0.523599));
		height = (map->res_y / 2) - (map->sprite[nb_sprite].size / 2);
		if (height < 0)
			height = 0;
		//if (width_right < 320)
		//{
			while (bottom > height)
			{
		/*
			
		   pixel = (i * map->image[0].line_bytes) + (x * 4);
			map->image[0].mlx_get_data[pixel + 0]
				= map->image[5].mlx_get_data[(((i%64) * map->image[5].line_bytes) + (x_sprite_s)*4) + 0];
			map->image[0].mlx_get_data[pixel + 1]
				= map->image[5].mlx_get_data[(((i%64) * map->image[5].line_bytes) + (x_sprite_s)*4) + 1];
			map->image[0].mlx_get_data[pixel + 2]
				= map->image[5].mlx_get_data[(((i%64) * map->image[5].line_bytes) + (x_sprite_s)*4) + 2];
			map->image[0].mlx_get_data[pixel + 3]
				= map->image[5].mlx_get_data[(((i%64) * map->image[5].line_bytes) + (x_sprite_s)*4) + 3];
		*/
			pixel = (height * map->image[0].line_bytes) + (width_left * 4);
			map->image[0].mlx_get_data[pixel + 0]
				= map->image[5].mlx_get_data[(((height%64) * map->image[5].line_bytes) + (u)*4) + 0];
			map->image[0].mlx_get_data[pixel + 1]
				= map->image[5].mlx_get_data[(((height%64) * map->image[5].line_bytes) + (u)*4) + 1];
			map->image[0].mlx_get_data[pixel + 2]
				= map->image[5].mlx_get_data[(((height%64) * map->image[5].line_bytes) + (u)*4) + 2];
			map->image[0].mlx_get_data[pixel + 3]
				= map->image[5].mlx_get_data[(((height%64) * map->image[5].line_bytes) + (u)*4) + 3];
			height++;
			}
		//}
		width_left++;
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
			map->image[0].mlx_get_data[pixel + 3] = (ceil_colour >> 24) & 0xFF;
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
			map->image[0].mlx_get_data[pixel + 3] = (floor_colour >> 24) & 0xFF;
			i++;
		}
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
	/** Source : https://fr.wikipedia.org/wiki/Z-buffer **/
	double	*z_buffer;
	size_t	number_lines;
	int	number_tex;
	int side = 0;
	z_buffer = malloc(sizeof(double) * ((double)map->res_x + 1.0));
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
		t_image *test;

		if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall)
		{
			if (map->player.degree > 0.0 && map->player.degree < 180.0)
				test = &map->image[1];
			else
				test = &map->image[4];
			map->player.distance_wall = map->player.ray_horizontal.distance_wall;
			map->player.offset_tex = map->player.ray_horizontal.length_case_x;
			*(z_buffer + x) = map->player.ray_horizontal.length_case_x;
		}
		else
		{
			if (map->player.degree > 90.0 && map->player.degree < 270.0)
				test = &map->image[2];
			else
				test = &map->image[3];
			map->player.distance_wall = map->player.ray_vertical.distance_wall;
			map->player.offset_tex = map->player.ray_vertical.length_case_y;
			*(z_buffer + x) = map->player.ray_vertical.length_case_y;
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
				map->player.bottom_wall = map->res_y;
		//map->player.height_wall = map->res_y - map->player.bottom_wall;
		//put_pixel(map, x, map->image[0].line_bytes, map->image[0].bpp, manage_bit_colour_ceiling(map));
		ceil_mapping(map, x, manage_bit_colour_ceil(map));
		texture_mapping(map, pos_u, x, square_size, test);
		floor_mapping(map, x, manage_bit_colour_floor(map));
		map->player.degree -= add_degree;
		correct_degree += add_degree;
		x++;
	}
	*(z_buffer + x) = 0;
	unsigned int	nb_sprite = map->nb_sprite;
	//on calcule la distance comme un ray
	while (nb_sprite > 0)
	{
		nb_sprite--;
		map->sprite[nb_sprite].distance = sqrt(pow((double)map->sprite[nb_sprite].y - (square_size * (map->player.pos_y + 1.0)), 2)
				+ pow((double)map->sprite[nb_sprite].x - (square_size * (map->player.pos_x + 1.0)), 2));
		map->sprite[nb_sprite].distance = map->sprite[nb_sprite].distance / 64.0;
		map->sprite[nb_sprite].degree = atan2(map->sprite[nb_sprite].y - (square_size * (map->player.pos_y + 1.0)), map->sprite[nb_sprite].x - (square_size * (map->player.pos_x + 1.0)));
		map->sprite[nb_sprite].degree = (-map->sprite[nb_sprite].degree) - degree_to_radian(map->player.degree_raycast);
		map->sprite[nb_sprite].degree = correct_distance(radian_to_degree(map->sprite[nb_sprite].degree));
		map->sprite[nb_sprite].degree = degree_to_radian(map->sprite[nb_sprite].degree);
		map->sprite[nb_sprite].size = ((map->res_x / 2) / tan(0.523599)) / (cos(map->sprite[nb_sprite].degree) * (map->sprite[nb_sprite].distance));
		// signe - car degree inverse
		//map->sprite[nb_sprite].size = 64.0 / map->sprite[nb_sprite].distance * ((map->res_x / 2) / tan(0.523599)),
		//map->sprite[nb_sprite].degree = correct_distance(radian_to_degree(map->sprite[nb_sprite].degree));
		//map->sprite[nb_sprite].x_sprite = (map->sprite[nb_sprite].degree * map->res_x / 60.0);
		map->sprite[nb_sprite].x_sprite = tan(map->sprite[nb_sprite].degree) * ((map->res_x / 2) / tan(0.523599));
		map->sprite[nb_sprite].x_sprite = -map->sprite[nb_sprite].x_sprite;
		sprite_mapping(map, nb_sprite);
	}
	//while (map->res_x > z)
	//{
	//if (map->sprite[0].x_sprite >= 0 && map->sprite[0].x_sprite <= 360)
	//	z++;
//	}
	free(z_buffer);
}
