#include "../../includes/cub.h"
#include <stdio.h>

void	shortest_ray_from_pos(t_map *map)
{
	if (map->player.dir_x < 0)
	{
		map->player.step_x = -1;
		map->player.side_ray_x = (map->player.pos_x - map->player.fill_x)
			* map->player.length_x;
	}
	else
	{
		map->player.step_x = 1;
		map->player.side_ray_x = (map->player.fill_x + 1.00 - map->player.pos_x)
			* map->player.length_x;
	}
	if (map->player.dir_y < 0)
	{
		map->player.step_y = -1;
		map->player.side_ray_y = (map->player.pos_y - map->player.fill_y)
			* map->player.length_y;
	}
	else
	{
		map->player.step_y = 1;
		map->player.side_ray_y = (map->player.fill_y + 1.00 - map->player.pos_y)
			* map->player.length_y;
	}
}

void	loop_until_wall(t_map *map)
{
	map->player.is_wall = 0;
	while (!map->player.is_wall)
	{
		if (map->player.side_ray_y > map->player.side_ray_x)
		{
			map->player.side_ray_x += map->player.length_x;
			printf("sideray_x=%f\n", map->player.side_ray_x);
			map->player.fill_x += map->player.step_x;
			map->player.side_ray = 0;
		}
		else
		{
			map->player.side_ray_y += map->player.length_y;
			printf("sideray_y=%f\n", map->player.side_ray_y);
			map->player.fill_y += map->player.step_y;
			map->player.side_ray = 1;	
		}
		printf("map[y][x]=%c", map->lines[map->player.fill_y][map->player.fill_x]);
		if (map->lines[map->player.fill_y][map->player.fill_x] != '0')
			map->player.is_wall = 1;
		printf("side_ray=%d\n", map->player.side_ray);
		map->player.step_x = 0;
		/** -1 for not going being map case **/
		printf("calcule=%f\n",
			map->player.perpendicular_distance = (map->player.fill_x - map->player.pos_x + (1 - map->player.step_x) / 2) / map->player.dir_x);
		if (map->player.side_ray == 0)
			map->player.perpendicular_distance = (map->player.fill_x - map->player.pos_x + (1 - map->player.step_x) / 2) / map->player.dir_x;
		else
			map->player.perpendicular_distance = (map->player.fill_y - map->player.pos_y + (1 - map->player.step_y) / 2) / map->player.dir_y;
	}
	printf("\n");
}

void	camera_wall(t_map *map)
{
	int	x;
	double	ratio;

	x = 0;
	while (map->res_x > x)
	{
		/** camera angle start ray, must give vector ray**/
		ratio = 2 * x / (double)map->res_x;
		map->player.dir_x = (cos(M_PI)/3) + (cos(M_PI - ((M_PI * 2) / 60))) * ratio;
		/** sin side **/
		map->player.dir_y = (sin(M_PI)/3) + (sin(M_PI - ((M_PI * 2) / 60))) * ratio;
		/** round for the least number **/
		map->player.fill_x = ceil(map->player.pos_x);
		map->player.fill_y = ceil(map->player.pos_y);
		//printf("sqrt=%f\n", sqrt(1 + (map->player.dir_y * map->player.dir_y) / (map->player.dir_x * map->player.dir_x)));
		map->player.length_y = sqrt(1 + (map->player.dir_x * map->player.dir_x) / (map->player.dir_y * map->player.dir_y));
		map->player.length_x = sqrt(1 + (map->player.dir_y * map->player.dir_y) / (map->player.dir_x * map->player.dir_x));
		shortest_ray_from_pos(map);
		loop_until_wall(map);
		x++;
	}
	map->player.middle_wall = (int)map->res_y / map->player.perpendicular_distance;
	map->player.bottom_pixel = 
	printf("fill_x=%d\n", map->player.fill_x);
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
	printf("wall height=%d\n", map->player.middle_wall);
}
