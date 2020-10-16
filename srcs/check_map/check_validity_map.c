#include "../../includes/cub.h"
#include <stdio.h>
static void	init_flood_fill(int is_valid_case[8][2])
{
	is_valid_case[0][0] = 1;
	is_valid_case[1][0] = 1;
	is_valid_case[2][0] = 0;
	is_valid_case[3][0] = -1;
	is_valid_case[4][0] = -1;
	is_valid_case[5][0] = -1;
	is_valid_case[6][0] = 0;
	is_valid_case[7][0] = 1;
	is_valid_case[0][1] = 0;
	is_valid_case[1][1] = 1;
	is_valid_case[2][1] = 1;
	is_valid_case[3][1] = 1;
	is_valid_case[4][1] = 0;
	is_valid_case[5][1] = -1;
	is_valid_case[6][1] = -1;
	is_valid_case[7][1] = -1;
}

// || is_space(map->check_lines[y + array[i][0]][x + array[i][1]]))
static void	check_case_around(t_map *map, int x, int y)
{
	int	i;
	int	array[8][2];

	i = 0;
	init_flood_fill(array);
	while (i != 8)
	{
		if (y - 1 >= 0)
		{
			if (!map->lines[y][x] || !map->lines[y + 1]
					|| !map->lines[y - 1]
					|| !map->lines[y + array[i][0]][x + array[i][1]])
				close_program_gnl(map, "Map case invalid.\n", 2);
		}
		else
			close_program_gnl(map, "Map case invalid.\n", 2);
		i++;
	}
}

static void	flood_fill(t_map *map, int x, int y, char old_value)
{
	if (map->lines)
	{
		old_value = map->lines[y][x];
		check_case_around(map, x, y);
		if (map->lines[y][x] == old_value)
		{
			map->lines[y][x] = '1';
			if (map->lines[y + 1][x] != '1'
					&& map->lines[y + 1][x] != ' ')
				flood_fill(map, x, y + 1, old_value);
			if (map->lines[y - 1][x] != '1'
					&& map->lines[y - 1][x] != ' ')
				flood_fill(map, x, y - 1, old_value);
			if (map->lines[y][x + 1] != '1' && map->lines[y][x + 1] != ' ')
				flood_fill(map, x + 1, y, old_value);
			if (map->lines[y][x - 1] != '1' && map->lines[y][x - 1] != ' ')
				flood_fill(map, x - 1, y, old_value);
		}
	}
}

static void	assignate_array(short *is_valid_array, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (map->colour_counter == 6)
		is_valid_array[0] = 1;
	if (map->is_north == 1)
		is_valid_array[1] = 1;
	if (map->is_east == 1)
		is_valid_array[2] = 1;
	if (map->is_west == 1)
		is_valid_array[3] = 1;
	if (map->is_south == 1)
		is_valid_array[4] = 1;
	if (map->is_sprite == 1)
		is_valid_array[5] = 1;
	if (map->is_resolution == 2)
		is_valid_array[6] = 1;
	while (j != 7)
	{
		if (is_valid_array[j] == 0)
			close_program_gnl(map, "Some setting(s) from the map are wrongs.\n", 2);
		j++;
	}
}

int		check_validity_map(t_map *map)
{
	short	is_valid_array[9];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 9)
	{
		is_valid_array[i] = 0;
		i++;
	}
	assignate_array(&is_valid_array[0], map);
	if (check_valid_character(map) == 0)
	{
		is_valid_array[7] = search_player(map, map->lines, j);
		flood_fill(map, map->player.pos_x,
				map->player.pos_y,
				map->lines[map->player.pos_y][map->player.pos_x]);
		is_valid_array[8] = 1;
		printf("\n");
	}
	if (is_valid_array[7] != 1)
		close_program_gnl(map, "No player found or too much player.\n", 2);
	if (is_valid_array[8] != 1)
		close_program_gnl(map, "Something went wrong with map cases.\n", 2);
	return (0);
}
