#include "../includes/cub.h"

void	init_player(t_map *map)
{
	map->player.fill_x = 0;
	map->player.fill_y = 0;
	map->player.pos_x = 0;
	map->player.pos_y = 0;
	map->player.ray_dir_x = 0;
	map->player.ray_dir_y = 0;
	map->player.step_x = 0;
	map->player.step_y = 0;
	map->player.side_ray_x = 0;
	map->player.side_ray_y = 0;
	map->player.side_ray = 0;
	map->player.degree = 0;
	map->player.degree_raycast = 0;
	map->player.ray_horizontal.length_case_x = 0;
	map->player.ray_horizontal.length_case_y = 0;
	map->player.perpendicular_distance = 0;
	map->player.ray_horizontal.is_wall = 0;
	map->player.ray_vertical.is_wall = 0;
	map->player.bottom_wall = 0;
	map->player.height_wall = 0;
}

int	close_program_key(int keycode, void *param, char *message, int msg_number)
{
	int	i;
	t_map *map;

	i = 0;
	map = (t_map *)param;
	if (keycode == 65307)
	{
		close_program_ok(map, message, msg_number);
		exit(0);
		return (0);
	}
	return (0);
}
#include <stdio.h>
int	search_player(t_map *map, char **lines, int i)
{
	int j;

	j = 0;
	if (lines)
	{
		while (lines[i])
		{
			j = 0;
			while (lines[i][j] != '\0')
			{
				if (lines[i][j] == 'N' || lines[i][j] == 'S'
					|| lines[i][j] == 'E' || lines[i][j] == 'W')
				{
					map->player_exist++;
					map->player.pos_y = (double)i;
					map->player.pos_x = (double)j;
					map->player.fill_y = i;
					map->player.fill_x = j;
				}
				j++;
			}
			i++;
		}
	}
	if (map->player_exist != 1)
		close_program_gnl(map, "No player in the map, or too much.\n", 2);
	return (1);
}
#include <stdio.h>
int	control_player(int keycode, void *param)
{
	t_map *map;

	map = (t_map *)param;
	//printf("key=%d ", keycode);
	if (keycode == 'w')
	{
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.pos_y -= 0.2;
	}
	else if (keycode == 115)
	{
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.pos_y += 0.2;
	}
	else if (keycode == 97)
	{
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.pos_x -= 0.2;
	}
	else if (keycode == 100)
	{
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.pos_x += 0.2;
	}
	else if (keycode == 65361)
	{
		printf("degree=%f ", map->player.degree_raycast);
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.degree_raycast = correct_distance(map->player.degree_raycast + 2.0);
	}
	else if (keycode == 65363)
	{
		black_pixel(map, map->res_x, map->image[0].line_bytes, map->image[0].bpp, black_colour(map));
		map->player.degree_raycast = correct_distance(map->player.degree_raycast) - 2.0;
	}
	else if (keycode == 65307)
		close_program_key(keycode, param, "Closed OK.\n", 1);
	return (0);
}
