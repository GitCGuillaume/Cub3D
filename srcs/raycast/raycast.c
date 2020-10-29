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
	return (pi * M_PI/180);
}

void	vertical_detection(t_map *map)
{
	int	square_size;

	square_size = map->res_x / 5;
	map->player.ray_vertical.is_wall = 0;
	map->player.ray_vertical.distance_y = -square_size * tan(M_PI/3);
	map->player.ray_vertical.distance_x = square_size;
	map->player.ray_vertical.pos_y = square_size * (map->player.pos_y + 1);
	map->player.ray_vertical.pos_x = (map->player.pos_x + 1) * square_size;
	map->player.ray_vertical.pos_y -=32;
	map->player.ray_vertical.pos_x -=32;
	printf("distance_y=%f player_pos_x=%f pos_x=%d\n", map->player.ray_vertical.distance_y, map->player.pos_x, map->player.ray_vertical.pos_x);
	printf("(PX=%d / %d) * %d + %d", map->player.ray_vertical.pos_x, square_size, square_size, square_size);
	map->player.ray_vertical.inter_x = floor(floor(map->player.ray_vertical.pos_x) / square_size) * square_size + square_size;
	map->player.ray_vertical.inter_y = map->player.ray_vertical.pos_y + (map->player.ray_vertical.pos_x - map->player.ray_vertical.inter_x) * tan(M_PI/3);
	printf("inter_y=%f\ninter_x=%f\nxa=%f\n", map->player.ray_vertical.inter_y, map->player.ray_vertical.inter_x, map->player.ray_vertical.distance_x);

	map->player.ray_vertical.length_case_x = map->player.ray_vertical.inter_x + map->player.ray_vertical.distance_x;
	map->player.ray_vertical.length_case_y = map->player.ray_vertical.inter_y + map->player.ray_vertical.distance_y;
	printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_vertical.distance_y, map->player.ray_vertical.distance_x, map->player.ray_vertical.length_case_x, map->player.ray_vertical.length_case_y, map->player.ray_vertical.is_wall);
	if (map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size] == '0')
	{
		while (map->player.ray_vertical.is_wall == 0)
		{
			map->player.ray_vertical.length_case_x += floor(map->player.ray_vertical.distance_x);
			map->player.ray_vertical.length_case_y += map->player.ray_vertical.distance_y;
			if (map->lines[(int)map->player.ray_vertical.length_case_y / square_size] && map->lines[(int)map->player.ray_vertical.length_case_y / square_size][(int)map->player.ray_vertical.length_case_x / square_size] != '0')
				map->player.ray_vertical.is_wall = 1;
		}
	}
	printf("xa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_vertical.distance_x, map->player.ray_vertical.length_case_x, map->player.ray_vertical.length_case_y, map->player.ray_vertical.is_wall);


}
void	horizontal_detection(t_map *map)
{
	/** height grill and x intersection between 2 cases**/
	int	square_size;

	square_size = map->res_x / 5;
	map->player.ray_horizontal.distance_y = -square_size;
	map->player.ray_horizontal.distance_x = square_size / tan(degree_to_radian(60));
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
	map->player.ray_horizontal.inter_y = floor(map->player.ray_horizontal.pos_y / square_size) * square_size - 1;
	printf("%d + (%d - %f)/tan(60)", map->player.ray_horizontal.pos_x, map->player.ray_horizontal.pos_y, map->player.ray_horizontal.inter_y);
	map->player.ray_horizontal.inter_x = map->player.ray_horizontal.pos_x + (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.inter_y) / tan(degree_to_radian(60));
	printf("square_size=%d\npos_y=%dpos_x=%d\n", square_size, map->player.ray_horizontal.pos_y, map->player.ray_horizontal.pos_x);
	printf("inter_y=%f\ninter_x=%f\nxa=%f\n", map->player.ray_horizontal.inter_y, map->player.ray_horizontal.inter_x, floor(map->player.ray_horizontal.distance_x));
	map->player.ray_horizontal.is_wall = 0;
	map->player.ray_horizontal.length_case_x = map->player.ray_horizontal.inter_x + map->player.ray_horizontal.distance_x;
	map->player.ray_horizontal.length_case_y = map->player.ray_horizontal.inter_y + map->player.ray_horizontal.distance_y;
	
	printf("[][]=%c\n", map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size]);
	printf("ya=%f\nxa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_horizontal.distance_y, map->player.ray_horizontal.distance_x, map->player.ray_horizontal.length_case_x, map->player.ray_horizontal.length_case_y, map->player.ray_horizontal.is_wall);
	if (map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size] == '0')
	{
		while (map->player.ray_horizontal.is_wall == 0)
		{
			map->player.ray_horizontal.length_case_x += floor(map->player.ray_horizontal.distance_x);
			map->player.ray_horizontal.length_case_y += map->player.ray_horizontal.distance_y;
			if (map->lines[(int)map->player.ray_horizontal.length_case_y / square_size] && map->lines[(int)map->player.ray_horizontal.length_case_y / square_size][(int)map->player.ray_horizontal.length_case_x / square_size] != '0')
				map->player.ray_horizontal.is_wall = 1;
		}
	}
	printf("xa=%f\nlength_x=%f\nlength_y=%f\nis_wall=%d\n", map->player.ray_horizontal.distance_x, map->player.ray_horizontal.length_case_x, map->player.ray_horizontal.length_case_y, map->player.ray_horizontal.is_wall);
	//printf("a=%f\n", map->player.inter_y);
}

void	raycast(t_map *map)
{
	int	x;

	x = 0;
	if (!(start_ray_direction(map)))
		exit(0);
	map->player.ray_dir = map->player.pi_x + map->player.pi_y;
	printf("ray_dir_y=%f\nray_dir_x=%f\nraydir=%f\n", map->player.pi_y, map->player.pi_x, map->player.ray_dir);
	
	//map->player.pi_x = cos((2*M_PI)/3);
//	map->player.pi_y = sin((2*M_PI)/3);
//	map->player.ray_dir -= map->player.pi_x + map->player.pi_y;
	//while (map->res_x x)
	//{
	//	map->player.ray_dir += 0.0122;
	//	printf("ray_dir_y=%f\nray_dir_x=%f\nraydir=%f\n", map->player.pi_y, map->player.pi_x, map->player.ray_dir);
		
	horizontal_detection(map);
	vertical_detection(map);
	map->player.ray_horizontal.distance_wall = sqrt((map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
			* (map->player.ray_horizontal.pos_x - map->player.ray_horizontal.length_case_x)
			+ (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y)
			* (map->player.ray_horizontal.pos_y - map->player.ray_horizontal.length_case_y));
	map->player.ray_vertical.distance_wall = sqrt((map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
			* (map->player.ray_vertical.pos_x - map->player.ray_vertical.length_case_x)
			+ (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y)
			* (map->player.ray_vertical.pos_y - map->player.ray_vertical.length_case_y));

	printf("px=%d py=%d\n", map->player.ray_horizontal.pos_x, map->player.ray_horizontal.pos_y);
	printf("px=%d py=%d\n", map->player.ray_vertical.pos_x, map->player.ray_vertical.pos_y);
	printf("horizontal distance_wall=%f\n", map->player.ray_horizontal.distance_wall);
	printf("vertical distance_wall=%f\n", map->player.ray_vertical.distance_wall);
	//	x++;
	//}
}
