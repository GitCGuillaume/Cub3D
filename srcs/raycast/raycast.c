#include "../../includes/cub.h"

#include <stdio.h>

int	start_ray_direction(t_map *map)
{
	if (map->player.start_position == 'N')
	{
		map->player.degree = 90;
		return (1);
	}
	else if (map->player.start_position == 'S')
	{
		map->player.degree = 270;
		return (1);
	}
	else if (map->player.start_position == 'E')
	{
		map->player.degree = 0;
		return (1);
	}
	else if (map->player.start_position == 'W')
	{
		map->player.degree = 180;
		return (1);
	}
	return (0);
}

double	degree_to_radian(double pi)
{
	return ((pi * M_PI)/180);
}
/*
void	vertical_detection(t_map *map)
{
	int	square_size;

	square_size = map->res_x / 5;
	map->player.ray_vertical.is_wall = 0;
	map->player.ray_vertical.distance_y = -square_size * tan(degree_to_radian(map->player.degree));
	if ((90 > map->player.degree && map->player.degree <= 0) || (map->player.degree > 270 && map->player.degree < 360))
		map->player.ray_vertical.distance_x = square_size;
	else
		map->player.ray_vertical.distance_x = -square_size;
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1) * square_size;
	map->player.ray_vertical.pos_y -=32;
	map->player.ray_vertical.pos_x -=32;
	printf("distance_y=%f player_pos_x=%f pos_x=%d\n", map->player.ray_vertical.distance_y, map->player.pos_x, map->player.ray_vertical.pos_x);
	printf("(PX=%d / %d) * %d + %d", map->player.ray_vertical.pos_x, square_size, square_size, square_size);
	if ((90 > map->player.degree && map->player.degree <= 0) || (map->player.degree > 270 && map->player.degree < 360))
		map->player.ray_vertical.length_case_x = floor(floor(map->player.ray_vertical.pos_x) / square_size) * square_size + square_size;
	else
		map->player.ray_vertical.length_case_x = floor(floor(map->player.ray_vertical.pos_x) / square_size) * square_size - 1;
	map->player.ray_vertical.length_case_y = map->player.ray_vertical.pos_y + (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x) * tan(degree_to_radian(map->player.degree));
	//printf("inter_y=%f\ninter_x=%f\nxa=%f\n", map->player.ray_vertical.inter_y, map->player.ray_vertical.inter_x, map->player.ray_vertical.distance_x);

	//map->player.ray_vertical.length_case_x = map->player.ray_vertical.inter_x + map->player.ray_vertical.distance_x;
	//map->player.ray_vertical.length_case_y = map->player.ray_vertical.inter_y + map->player.ray_vertical.distance_y;
	//printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_vertical.distance_y, map->player.ray_vertical.distance_x, map->player.ray_vertical.length_case_x, map->player.ray_vertical.length_case_y, map->player.ray_vertical.is_wall);
	*//*if (map->player.ray_vertical.length_case_y < 0)
		map->player.ray_vertical.length_case_y = 0;
	if (map->player.ray_vertical.length_case_x < 0)
		map->player.ray_vertical.length_case_x = 0;
	*/
	//printf("map->[][]=%c\n", map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size]);
	//if (map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size] == '0')
	//{
	/*	while (map->player.ray_vertical.is_wall == 0)
		{
			if (map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size] != '0')
			{
				map->player.ray_vertical.is_wall = 1;
			}
			else
			{
				map->player.ray_vertical.length_case_x += floor(map->player.ray_vertical.distance_x);
				map->player.ray_vertical.length_case_y += map->player.ray_vertical.distance_y;
			}
		}
	//}
	if (map->player.ray_vertical.length_case_y < 0)
		map->player.ray_vertical.length_case_y = 0;
	if (map->player.ray_vertical.length_case_x < 0)
		map->player.ray_vertical.length_case_x = 0;
	printf("xa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_vertical.distance_x, map->player.ray_vertical.length_case_x, map->player.ray_vertical.length_case_y, map->player.ray_vertical.is_wall);


}*/

void	vertical_detection(t_map *map)
{
	/** height grill and x intersection between 2 cases**/
	int	square_size;

	square_size = map->res_x / 5;
	//map->player.ray_vertical.distance_x = square_size;
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1) * square_size;
	map->player.ray_vertical.pos_y -=32;
	map->player.ray_vertical.pos_x -=32;
	/** GET HIGHEST Y side of the case from current position **/
	printf("degree=%d\n", map->player.degree);
	if (map->player.degree > 90 && map->player.degree < 270)
		map->player.ray_vertical.length_case_x = floor(map->player.ray_vertical.pos_x / square_size) * square_size - 1;
	else
		map->player.ray_vertical.length_case_x = floor(map->player.ray_vertical.pos_x / square_size) * square_size + square_size;
	map->player.ray_vertical.length_case_y = map->player.ray_vertical.pos_y + (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x) * tan(degree_to_radian(map->player.degree));
	//FIND CASE Y
	map->player.ray_vertical.distance_y = square_size * tan(degree_to_radian(map->player.degree));
	
	printf("tan=%f\nsquare_size=%d\ndis_y=%f\npos_y=%dpos_x=%d\n", tan(degree_to_radian(map->player.degree)), square_size, map->player.ray_vertical.distance_y, map->player.ray_vertical.pos_y, map->player.ray_vertical.pos_x);
	map->player.ray_vertical.distance_y = -map->player.ray_vertical.distance_y;
	//FIND CASE X
	if (map->player.degree > 90 && map->player.degree < 270)
	{
		map->player.ray_vertical.distance_x = -square_size;
	}
	else
	{
		map->player.ray_vertical.distance_x = square_size;
	}
	map->player.ray_vertical.is_wall = 0;
	while (map->player.ray_vertical.is_wall == 0)
		{
			if (map->lines[(int)map->player.ray_vertical.length_case_y / square_size] && map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size] != '0')
			{
				map->player.ray_vertical.is_wall = 1;
			}
			else
			{
				map->player.ray_vertical.length_case_x += floor(map->player.ray_vertical.distance_x);
				map->player.ray_vertical.length_case_y += map->player.ray_vertical.distance_y;
			}
		}
	//}
	printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_vertical.distance_y, map->player.ray_vertical.distance_x, map->player.ray_vertical.length_case_x, map->player.ray_vertical.length_case_y, map->player.ray_vertical.is_wall);
}


void	horizontal_detection(t_map *map)
{
	/** height grill and x intersection between 2 cases**/
	int	square_size;

	square_size = map->res_x / 5;
	map->player.ray_horizontal.distance_y = square_size;
	map->player.ray_horizontal.pos_y = square_size * (map->player.pos_y + 1);
	map->player.ray_horizontal.pos_x = (map->player.pos_x + 1) * square_size;
	map->player.ray_horizontal.pos_y -=32;
	map->player.ray_horizontal.pos_x -=32;
	//float aTan=-1/tan(map->player.pi_y);
	//printf("aTan=%f\n", aTan);
	//printf("sin(degtorad())=%f\n", degree_to_radian(map->player.pi_y));
//	if (map->player.pi_y > )

	/** GET HIGHEST Y side of the case from current position **/
	//map->player.inter_y = ceil(pos_y / square_size) * square_size;
	printf("degree=%d\n", map->player.degree);
	if (map->player.degree > 0 && map->player.degree < 180)
		map->player.ray_horizontal.length_case_y = floor(map->player.ray_horizontal.pos_y / square_size) * square_size - 1;
	else
		map->player.ray_horizontal.length_case_y = floor(map->player.ray_horizontal.pos_y / square_size) * square_size + square_size;
//	printf("%d + (%d - %f)/tan(60)", map->player.ray_horizontal.pos_x, map->player.ray_horizontal.pos_y, map->player.ray_horizontal.inter_y);
	map->player.ray_horizontal.length_case_x = map->player.ray_horizontal.pos_x + (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y) / tan(degree_to_radian(map->player.degree));
	
	//FIND YA
	if (map->player.degree > 0 && map->player.degree < 180)
		map->player.ray_horizontal.distance_y = -square_size;
	else
		map->player.ray_horizontal.distance_y = square_size;
	//FIND XA
	map->player.ray_horizontal.distance_x = square_size / tan(degree_to_radian(map->player.degree));
	
	printf("square_size=%d\npos_y=%dpos_x=%d\n", square_size, map->player.ray_horizontal.pos_y, map->player.ray_horizontal.pos_x);
	//printf("inter_y=%f\ninter_x=%f\nxa=%f\n", map->player.ray_horizontal.inter_y, map->player.ray_horizontal.inter_x, floor(map->player.ray_horizontal.distance_x));
	map->player.ray_horizontal.is_wall = 0;
	//map->player.ray_horizontal.length_case_x = map->player.ray_horizontal.inter_x + map->player.ray_horizontal.distance_x;
	//map->player.ray_horizontal.length_case_y = map->player.ray_horizontal.inter_y + map->player.ray_horizontal.distance_y;
	//printf("[][]=%c\n", map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size]);
	//if (map->player.ray_vertical.length_case_y < 0)
	//	map->player.ray_vertical.length_case_y = 0;
//	if (map->player.ray_vertical.length_case_x < 0)
//		map->player.ray_vertical.length_case_x = 0;
//	printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_horizontal.distance_y, map->player.ray_horizontal.distance_x, map->player.ray_horizontal.length_case_x, map->player.ray_horizontal.length_case_y, map->player.ray_horizontal.is_wall);
	//if (map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size] == '0')
	//{
		while (map->player.ray_horizontal.is_wall == 0)
		{
			if (map->lines[(int)map->player.ray_horizontal.length_case_y / square_size] && map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size] != '0')
			{
				map->player.ray_horizontal.is_wall = 1;
			}
			else
			{
				map->player.ray_horizontal.length_case_x += floor(map->player.ray_horizontal.distance_x);
				map->player.ray_horizontal.length_case_y += map->player.ray_horizontal.distance_y;
			}
		}
	//}
	printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_horizontal.distance_y, map->player.ray_horizontal.distance_x, map->player.ray_horizontal.length_case_x, map->player.ray_horizontal.length_case_y, map->player.ray_horizontal.is_wall);
	//printf("a=%f\n", map->player.inter_y);
}

void	raycast(t_map *map)
{
	int	x;
	double	fisheye;
	int	slice_height;
	int	square_size;
	double	add_degree;

	square_size = map->res_x / 5;
	x = 0;
	if (!(start_ray_direction(map)))
		exit(0);
	//map->player.degree += 30;
	add_degree = 60 / map->res_x;
	while (map->res_x > x)
	{
		if (map->player.degree == 0 || map->player.degree == 90 || map->player.degree == 180 || map->player.degree == 270)
			map->player.degree = map->player.degree + 0.000001;
		printf("horizontal\n");
		horizontal_detection(map);
		printf("vertical\n");	
		vertical_detection(map);
		//exit(0);
		printf("end\n");
		map->player.ray_horizontal.distance_wall = sqrt(((map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
				* (map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x))
				+ ((map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)
				* (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)));
		map->player.ray_vertical.distance_wall = sqrt(((map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
				* (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x))
				+ ((map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)
				* (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)));
		printf("horizontal_d=%f\nvertical_d=%f\n", map->player.ray_horizontal.distance_wall, map->player.ray_vertical.distance_wall);
		if (map->player.ray_horizontal.distance_wall < map->player.ray_vertical.distance_wall)
			map->player.distance_wall = map->player.ray_horizontal.distance_wall /** cos(degree_to_radian(map->player.degree *//*- 30*//*))*/;
		else
			map->player.distance_wall = map->player.ray_vertical.distance_wall /** cos(degree_to_radian(map->player.degree *//*+ 30*//*))*/;
		map->player.slice_height = square_size * 277 / map->player.distance_wall;
		map->player.bottom_wall = (map->res_y / 2) + floor(map->player.slice_height /2);
		if (map->player.bottom_wall > map->res_y)
				map->player.bottom_wall = map->res_y-1;
		map->player.height_wall = map->res_y - map->player.bottom_wall;
		if (map->player.height_wall < 0)
			map->player.height_wall = 0;
		put_pixel(map, x, map->image[0].line_bytes, map->image[0].bpp, manage_bit_colour_ceiling(map));
		printf("distance_wall=%f\nslice_height=%d\nbottom_wall=%d\ntop_wall=%d\n", map->player.distance_wall, map->player.slice_height, map->player.bottom_wall, map->player.height_wall);
		//printf("px=%d py=%d\n", map->player.ray_horizontal.pos_x, map->player.ray_horizontal.pos_y);
		//printf("px=%d py=%d\n", map->player.ray_vertical.pos_x, map->player.ray_vertical.pos_y);
	//	printf("horizontal distance_wall=%f\n", map->player.ray_horizontal.distance_wall);
	//	printf("vertical distance_wall=%f\n", map->player.ray_vertical.distance_wall);
		map->player.degree -= add_degree;
		x++;
	}
}
