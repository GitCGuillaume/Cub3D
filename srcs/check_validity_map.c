#include "../includes/cub.h"
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

static void	check_case_around(t_map *map, int x, int y)
{
	int	i;
	int	array[8][2];

	i = 0;
	init_flood_fill(array);
	while (i != 8)
	{
		if (!map->check_lines[y + 1] || !map->check_lines[y - 1]
			|| !map->check_lines[y + array[i][0]][x + array[i][1]]
			|| is_space(map->check_lines[y + array[i][0]][x + array[i][1]]))
			close_program(map);
		i++;
	}
}

static void	flood_fill(t_map *map, int x, int y, char old_value)
{
	old_value = map->check_lines[y][x];
	check_case_around(map, x, y);
	if (map->lines[y][x] == old_value)
	{
		map->check_lines[y][x] = '1';
		if (map->check_lines[y + 1][x] != '1')
			flood_fill(map, x, y + 1, old_value);
		if (map->check_lines[y - 1][x] != '1')
			flood_fill(map, x, y - 1, old_value);
		if (map->check_lines[y][x + 1] != '1')
			flood_fill(map, x + 1, y, old_value);
		if (map->check_lines[y][x - 1] != '1')
			flood_fill(map, x - 1, y, old_value);
	}
}

static void	assignate_array(short *is_valid_array, t_map *map)
{
	int		i;

	i = 0;
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
	is_valid_array[7] = search_player(map, i);
	flood_fill(map, map->player.pos_x,
		map->player.pos_y,
		map->check_lines[map->player.pos_y][map->player.pos_x]);
	is_valid_array[8] = 1;
}

int		check_validity_map(t_map *map)
{
	short	is_valid_array[9];
	int		i;

	i = 0;
	while (i != 9)
	{
		is_valid_array[i] = 0;
		i++;
	}
	assignate_array(&is_valid_array[0], map);
	i = 0;
	while (map->check_lines[i])
		i++;
	i = 0;
	while (i < 9)
	{
		if (is_valid_array[i] != 1)
		{
			ft_putstr_fd("error", 2);
			close_program(map);
		}
		i++;
	}
	return (0);
}
