#include "../../includes/cub.h"
#include <stdio.h>
/*
void	shortest_ray_from_pos(t_map *map)
{
	if (map->player.dir_x < 0)
	{
		map->player.step_x = -1;
		map->player.side_ray_x = (map->player.pos_x - map->player.fill_x) * map->player.length_case_x;
	}
	else
	{
		map->player.step_x = 1;
		map->player.side_ray_x = (map->player.fill_x + 1.0 - map->player.pos_x) * map->player.length_case_x;
	}
	if (map->player.dir_y < 0)
	{
		map->player.step_y = -1;
		map->player.side_ray_y = (map->player.pos_y - map->player.fill_y) * map->player.length_case_y;
	}
	else
	{
		map->player.step_y = 1;
		map->player.side_ray_y = (map->player.fill_y + 1.0 - map->player.pos_y) * map->player.length_case_y;
	}
}
*/
/*
void	loop_until_wall(t_map *map)
{
	map->player.is_wall = 0;
	while (!map->player.is_wall)
	{
		if (map->player.side_ray_y > map->player.side_ray_x)
		{
			map->player.side_ray_x += map->player.length_case_x;
			//printf("sideray_x=%f\n", map->player.side_ray_x);
			map->player.fill_x += map->player.step_x;
			map->player.side_ray = 0;
		}
		else
		{
			map->player.side_ray_y += map->player.length_case_y;
			//printf("sideray_y=%f\n", map->player.side_ray_y);
			map->player.fill_y += map->player.step_y;
			map->player.side_ray = 1;	
		}
*/
	//	printf("x=%d y=%d map[y][x]=%c\n", map->player.fill_x, map->player.fill_y, map->lines[map->player.fill_y][map->player.fill_x]);
		//printf("s=%s\n", map->lines[map->player.fill_y]);
//		if (map->lines[map->player.fill_y][map->player.fill_x] != '0')
//			map->player.is_wall = 1;
		//printf("side_ray=%d\n", map->player.side_ray);
		//map->player.step_x = 0;
		/** -1 for not going behind map case **/	
/*	}
	if (map->player.side_ray == 0)
		map->player.perpendicular_distance = (map->player.fill_x - map->player.pos_x + (1 - map->player.step_x) / 2) / map->player.dir_x;
	else
		map->player.perpendicular_distance = (map->player.fill_y - map->player.pos_y + (1 - map->player.step_y) / 2) / map->player.dir_y;
	if (map->player.perpendicular_distance == 0)
		map->player.perpendicular_distance = 0.000001;
	//map->player.perpendicular_distance = (map->player.fill_x - map->player.pos_x + (1 - map->player.step_x) / 2) / map->player.dir_x;
	//map->player.perpendicular_distance = (map->player.fill_y - map->player.pos_y + (1 - map->player.step_y) / 2) / map->player.dir_y;
	//printf("\n");
}
*/
int	start_ray_direction(t_map *map)
{
	if (map->player.start_position == 'N')
	{
		map->player.pi_x = cos(M_PI/2);
		map->player.pi_y = sin(M_PI/2);
		printf("pi_x=%f\n", map->player.pi_x);
		printf("pi_y=%f\n", map->player.pi_y);
		map->player.cross_x = cos(-M_PI);
		map->player.cross_y = sin(M_PI);
		printf("cross_x=%f\n", map->player.cross_x);
		printf("cross_y=%f\n", map->player.cross_y);
		
		printf("dir_y=%f\n", map->player.dir_y);
		printf("dir_x=%f\n", map->player.dir_x);
		return (1);
	}
	else if (map->player.start_position == 'S')
	{
		map->player.pi_x = cos(-M_PI/2);
		map->player.pi_y = sin(-M_PI/2);
		map->player.cross_x = cos(-M_PI);
		map->player.cross_y = sin(-M_PI);
		//map->player.dir_x = cos(-M_PI/2) + (cos(M_PI) /*- map->player.rotation_lr*/) * ratio;
		//map->player.dir_y = sin(-M_PI/2) + (sin(M_PI) /*+ map->player.rotation_lr*/) * ratio;
		return (1);

	}
	else if (map->player.start_position == 'E')
	{
		map->player.pi_x = cos(0);
		map->player.pi_y = sin(0);
		map->player.cross_x = cos(M_PI/2);
		map->player.cross_y = sin(M_PI/2);

		//map->player.dir_x = cos((0)) + (cos(M_PI/2) /*- map->player.rotation_lr*/) * ratio;
		//map->player.dir_y = sin((0)) + (sin(M_PI/2) /*+ map->player.rotation_lr*/) * ratio;
		return (1);
	}
	else if (map->player.start_position == 'W')
	{
		map->player.pi_x = cos(M_PI);
		map->player.pi_y = sin(M_PI);
		map->player.cross_x = cos(-M_PI/2);
		map->player.cross_y = sin(-M_PI/2);

		//map->player.dir_x = cos((M_PI)) + (cos(-M_PI/2) /*- map->player.rotation_lr*/) * ratio;
		//map->player.dir_y = sin((M_PI)) + (sin(-M_PI/2) /*+ map->player.rotation_lr*/) * ratio;
		return (1);
	}

	return (0);
}

void	camera_wall(t_map *map)
{
	int	x;
	double	ratio;

	x = 0;
	start_ray_direction(map);
	while (map->res_x > x)
	{
		/** camera angle start ray, must give vector ray**/
		//if (map->player.dir_y < 0)
		//else
		ratio = 2 * x / (double)map->res_x - 1;
		//map->player.dir_x = map->player.pi_x + (map->player.cross_x /*- map->player.rotation_lr*/) * ratio;
		//map->player.dir_y = map->player.pi_y + (map->player.cross_y /*+ map->player.rotation_lr*/) * ratio;
		//	printf("cos dir_x=%f sin dir_y=%f plane_x=%f plane_y=%f ratio=%f", cos(M_PI), sin(M_PI), cos(M_PI/2), sin(M_PI/2), ratio);
		//map->player.dir_x = cos(M_PI) + (cos(M_PI/2) /*- map->player.rotation_lr*/) * ratio;
		/** sin side **/
		//map->player.dir_y = sin(M_PI) + (sin(M_PI/2) /*+ map->player.rotation_lr*/) * ratio;
		//map->player.dir_y = -map->player.dir_y;
	//	printf("dir_y=%f\n", map->player.dir_y);
		/** round for the least number **/
		map->player.fill_x = ceil(map->player.pos_x);
		map->player.fill_y = ceil(map->player.pos_y);
	//	printf("dir_x=%f floor_x=%d floor_y=%d\n", map->player.dir_x, map->player.fill_x, map->player.fill_y);
		//printf("sqrt=%f\n", sqrt(1 + (map->player.dir_y * map->player.dir_y) / (map->player.dir_x * map->player.dir_x)));
		//if (map->player.dir_x == 0)
		//	map->player.length_x = 0;
		//else
		//	map->player.length_case_x = sqrt(1 + (map->player.dir_y * map->player.dir_y) / (map->player.dir_x * map->player.dir_x));
		//if (map->player.dir_y == 0)
		//	map->player.length_y = 0;
		//else
		//	map->player.length_case_y = sqrt(1 + (map->player.dir_x * map->player.dir_x) / (map->player.dir_y * map->player.dir_y));
		map->player.length_case_x = fabs(1/map->player.dir_x);
		map->player.length_case_y = fabs(1/map->player.dir_y);
		shortest_ray_from_pos(map);
		loop_until_wall(map);
		map->player.height_wall = (int)(map->res_y / map->player.perpendicular_distance);
		map->player.bottom_wall = -map->player.height_wall / 2 + map->res_y / 2;
		if (map->player.bottom_wall < 0)
			map->player.bottom_wall = 0;
		map->player.height_wall = map->player.height_wall / 2 + map->res_y / 2;
		if (map->player.height_wall >= map->res_y)
			map->player.height_wall = map->res_y-1;
		put_pixel(map, x, map->image[0].line_bytes, map->image[0].bpp, manage_bit_colour_ceiling(map));
		x++;
	/*int z = 0;
	while (map->lines[z])
	{
		printf("map->lines[x]=%s\n", map->lines[z]);
		z++;
	}*/

	}
	/*printf("\nfill_x=%d\n", map->player.fill_x);
	printf("fill_y=%d\n", map->player.fill_y);
	printf("pos_x=%f\n", map->player.pos_x);
	printf("pos_y=%f\n", map->player.pos_y);
	printf("dir_x=%f\n", map->player.dir_x);
	printf("dir_y=%f\n", map->player.dir_y);
	printf("step_x=%d\n", map->player.step_x);
	printf("step_y=%d\n", map->player.step_y);
	printf("length_x=%f\n", map->player.length_x);
	printf("length_y=%f\n", map->player.length_y);
	printf("side_ray_x=%f\n", map->player.side_ray_x);
	printf("side_ray_y=%f\n", map->player.side_ray_y);
	printf("perpendicular_ray=%f\n", map->player.perpendicular_distance);
	printf("is_wall=%d\n", map->player.is_wall);
	printf("wall height=%d\n", map->player.height_wall);
	printf("bottom_line=%d\n", map->player.bottom_wall);
	*/
}
