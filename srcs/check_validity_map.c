#include "../includes/cub.h"

int	check_full_wall(t_map *map, char *line)
{
	unsigned int	i;
	unsigned int	complete_wall;

	i = 0;
	complete_wall = 0;
	while (line[i] == '1' && line[i] != '\0')
	{
		printf("full wall");
		complete_wall++;
		i++;
	}
	printf("lineeuhhh = %s\n", line);
	if (line[i] != '\0' || complete_wall == 0)
	{
		complete_wall = 0;
		return (complete_wall);
	}
	return (complete_wall);
}

int	check_sides_walls(t_map *map, char *line)
{
	unsigned int	sides_walls;
	unsigned int	i;

	sides_walls = 0;
	i = 0;
	if (line[0] == '1' && line[i])
		sides_walls++;
	while (line[i] == '1' && line[i])
		i++;
	while ((line[i] == '0' || line[i] == 'N' || line[i] == 'E'
		|| line[i] == 'W' || line[i] == 'S' || line[i] == '2')
			&& line[i] != '\0')
	{
		sides_walls++;
		if (line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == 'S')
			map->player_exist++;
		i++;
	}
	if (line[i] != '1' || line[i] == '\0')
		return (0);
	return (1);
}

int	check_map_wall(t_map *map)
{
	unsigned short	is_valid_array[3];
	int	i;

	i = 0;
	while (map->lines[i][0] != '1' || map->lines[i][0] == '0' || map->lines[i][0] == '2')
		i++;
	if (map->lines[i] != NULL)
	{
		while (check_full_wall(map, map->lines[i]) == 1)
		{
			is_valid_array[0] = 1;
			i++;
		}
		while (check_sides_walls(map, map->lines[i]) == 1)
		{
			is_valid_array[1] += 1;
			i++;
		}
		while (check_full_wall(map, map->lines[i]) == 1)
		{
			is_valid_array[2] += 1;
			i++;
			//return (0);
		}
		printf("valid 0 = %d\n", is_valid_array[0]);
		printf("valid 1 = %d\n", is_valid_array[1]);
		printf("valid 2 = %d\n", is_valid_array[2]);
		
		/*if (is_valid_array[0] != 1 || is_valid_array[1] > 0
			|| is_valid_array[2] != 1)
			return (0);*/
	}
	return (1);
}

int	check_validity_map(t_map *map)
{
	unsigned short	is_valid_array[9];
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
	if (check_map_wall(map) == 1)
		is_valid_array[7] = 1;
	if (map->player_exist == 1)
		is_valid_array[8] = 1;
	while (is_valid_array[i] == 1)
		i++;
	
	printf("is_valid=%d\n", is_valid_array[0]);
	printf("is_valid=%d\n", is_valid_array[1]);
	printf("is_valid=%d\n", is_valid_array[2]);
	printf("is_valid=%d\n", is_valid_array[3]);
	printf("is_valid=%d\n", is_valid_array[4]);
	printf("is_valid=%d\n", is_valid_array[5]);
	printf("is_valid=%d\n", is_valid_array[6]);
	printf("is_valid=%d\n", is_valid_array[7]);
	printf("is_valid=%d\n", is_valid_array[8]);
	if (is_valid_array[i] == 0)
	{
		ft_putstr_fd("error", 1);
		exit (0);
	}
	return (0);
}
