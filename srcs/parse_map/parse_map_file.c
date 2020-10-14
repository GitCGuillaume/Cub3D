#include "../../includes/cub.h"
#include <stdio.h>

int	is_map_incorrect(int i, char *line, t_map *map)
{
	if (map->is_north != 1 || map->is_south != 1
		|| map->is_east != 1 || map->is_west != 1
		|| map->is_resolution != 2 || map->is_sprite != 1
		|| map->colour_counter != 6)
	{
		if (!(line[i] == 'R' && line[i + 1] == ' ')
			&& !(line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			&& !(line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			&& !(line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			&& !(line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
			&& !(line[i] == 'S' && line[i + 1] == ' ')
			&& !(line[i] == 'C' && line[i + 1] == ' ')
			&& !(line[i] == 'F' && line[i + 1] == ' '))
		{
			return (1);
		}
	}
	return (0);
}

int	is_line_correct(int i, char *line, t_map *map)
{
	if (map->is_north == 0 || map->is_south == 0
		|| map->is_east == 0 || map->is_west == 0
		|| map->is_resolution < 2 || map->is_sprite == 1
		|| map->colour_counter < 6)
	{
		if ((line[i] == 'R' && line[i + 1] == ' ')
			|| (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			|| (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
			|| (line[i] == 'S' && line[i + 1] == ' ')
			|| (line[i] == 'C' && line[i + 1] == ' ')
			|| (line[i] == '\0')
			|| (line[i] == 'F' && line[i + 1] == ' '))
		{
			return (1);
		}
	}
	return (0);
}

int	find_which_indicator(t_map *map, char *line)
{
	unsigned int	i;
	unsigned int	old_i;

	i = 0;
	while (is_tab(line[i]) || is_other(line[i]))
			i++;
	old_i = i;
	find_texture(line, old_i, map);
	find_texture_two(line, &i, old_i, map);
	if (line[old_i] == 'C' && line[old_i + 1] == ' ')
	{
		map->colour[3] = get_number_two(map, &i, line);
		if (line[i] == ',')
			map->colour[4] = get_number_two(map, &i, line);
		if (line[i] == ',')
			map->colour[5] = get_number_two(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
	}
	return (1);
}

char	*get_line_fd(t_map *map, int fd)
{
	char	*line;
	char	*tmp_line;
	char	*join_str;
	int	ret;
	int	i;

	line = NULL;
	tmp_line = NULL;
	join_str = NULL;
	line = ft_strdup("");
	i = 0;
	while ((ret = get_next_line(fd, &tmp_line)) > 0)
	{
		i = 0;
		while (tmp_line[i] == ' ' || tmp_line[i] == '\t')
			i++;
		find_which_indicator(map, tmp_line);
		if (check_indicator_full(map) == 7)	
		{
			join_str = ft_strjoin(line, tmp_line);
			free(line);
			line = join_str;
			free(tmp_line);
			tmp_line = ft_strjoin(line, "|");
			free(line);
			line = tmp_line;
		}
	}
	free(tmp_line);
	return (line);
}

int	check_configuration(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->lines[i])
	{
		find_which_indicator(map, map->lines[i]);
		i++;
	}
	if (map->colour_counter != 6)
	{
		close_program(map, "Configurations map colour is wrong, check RGB inputs number.\n", 2);
	}
	return (0);
}
#include <stdio.h>

int	is_full_line_ok(char *line)
{
	int	i;
	int	is_ok;

	i = 0;
	is_ok = 1;
	while (line[i] == '|' && line[i])
	{
		i++;
		is_ok = 1;
	}
	while(line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			is_ok = 0;
		i++;
	}
	return (is_ok);
}

int	parse_line_fd(t_map *map)
{
	int	i;
	int	mem_i;
	int	math_i;
	int	is_space_ok;

	i = 0;
	mem_i = 0;
	is_space_ok = 0;
	printf("colour counter=%d", map->colour_counter);
	is_space_ok = is_full_line_ok(map->full_line);
	if (is_space_ok > 0)
		map->lines = ft_split(map->full_line, '|');
	else
		close_program(map, "Map parameters wrongs, or space between map lines are here, remove them.\n", 2);
	printf("is_space_ok = %d\n", is_space_ok);
	printf("lines=%s\n", map->full_line);
	//map->check_lines = ft_split(map->full_line, '|');
	//check_configuration(map);
	printf("\nfull_line=%s\n", map->full_line);
	printf("north_path=%s", map->north_path);
	printf("south_path=%s", map->south_path);
	printf("east_path=%s", map->east_path);
	printf("west_path=%s", map->west_path);
	printf("sprite_path=%s", map->sprite_path);
	int k = 0;
	printf("\n");
	while (map->colour[k])
	{
		printf("map->colour[k]=%s\n", map->colour[k]);
		k++;
	}
	k = 0;
	while (map->resolution[k])
	{
		printf("map->resolution=%s\n", map->resolution[k]);
		k++;
	}
	printf("\n");
	if (map->colour_counter != 6)
	{
		close_program(map, "Configurations map colour is wrong, check RGB inputs number.\n", 2);
	}
	//i = check_first_character(map);
	//mem_i = i;
	//printf("i = %d", mem_i);
	//while (map->lines[i])
	//	i++;
	//math_i = i - mem_i;
	//map->map_case = malloc((sizeof(char *) * (math_i + 1)));
	//map->check_lines = malloc((sizeof(char *) * (math_i + 1)));
	//if (map->check_lines == NULL)
	//	close_program(map, "allocation memory failed.", 2);
	/*i = 0;
	while (math_i > i)
	{
		map->map_case[i] = ft_strdup(map->lines[mem_i]);
		map->check_lines[i] = ft_strdup(map->lines[mem_i]);
		mem_i++;
		i++;
	}
	map->map_case[i] = 0;
	map->check_lines[i] = 0;
	//if (is_map_incorrect(map) == 1)
	//	close_program(map, "Configuration file is incorrect.\n", 2);
	*/
	printf("-------\n");
	printf("is_north =%d\n", map->is_north);
	printf("is_east =%d\n", map->is_east);
	printf("is_west =%d\n", map->is_west);
	printf("is_south =%d\n", map->is_south);
	printf("is_sprite =%d\n", map->is_sprite);
	printf("is_resolution =%d\n", map->is_resolution);
	printf("colour_counter = %d\n", map->colour_counter);
	printf("r1=%s", map->resolution[0]);
	printf("r2=%s\n", map->resolution[1]);
	i = 0;
	while (map->lines[i])
	{
		printf("check_lines[i]==%s", map->lines[i]);
		i++;
	}
	check_validity_map(map);
	return (0);
}
