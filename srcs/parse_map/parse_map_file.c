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

int	is_line_incorrect(int i, char *line)
{
	printf("line=%c", line[i]);
	if ((line[i] != 'R' && line[i + 1] != ' ')
		&& (line[i] != 'N' && line[i + 1] != 'O' && line[i + 2] != ' ')
		&& (line[i] != 'S' && line[i + 1] != 'O' && line[i + 2] != ' ')
		&& (line[i] != 'W' && line[i + 1] != 'E' && line[i + 2] != ' ')
		&& (line[i] != 'E' && line[i + 1] != 'A' && line[i + 2] != ' ')
		&& (line[i] != 'S' && line[i + 1] != ' ')
		&& (line[i] != 'C' && line[i + 1] != ' ')
		&& (line[i] != '\0')
		&& (line[i] != 'F' && line[i + 1] != ' '))
	{
		return (1);
	}
	return (0);
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
		printf("is line incorrect = %d", is_line_incorrect(i, tmp_line));
		join_str = ft_strjoin(line, tmp_line);
		free(line);
		line = join_str;
		free(tmp_line);
		tmp_line = ft_strjoin(line, "|");
		free(line);
		line = tmp_line;
	}
	free(tmp_line);
	return (line);
}

int	find_which_indicator(t_map *map, char *line)
{
	unsigned int	i;
	unsigned int	old_i;

	i = 0;
	while (is_tab(line[i]) || is_other(line[i]))
		i++;
	old_i = i;
	if (is_map_incorrect(i, line, map))
		close_program(map, "Something went wront in the map setting, check characters.", 2);
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
int	parse_line_fd(t_map *map)
{
	int	i;
	int	mem_i;
	int	math_i;

	i = 0;
	mem_i = 0;
	map->lines = ft_split(map->full_line, '|');
	printf("lines=%s\n", map->full_line);
	//map->check_lines = ft_split(map->full_line, '|');
	check_configuration(map);
	i = check_first_character(map);
	mem_i = i;
	printf("i = %d", mem_i);
	while (map->lines[i])
		i++;
	math_i = i - mem_i;
	map->map_case = malloc((sizeof(char *) * (math_i + 1)));
	map->check_lines = malloc((sizeof(char *) * (math_i + 1)));
	if (map->check_lines == NULL)
		close_program(map, "allocation memory failed.", 2);
	i = 0;
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
	while (map->check_lines[i])
	{
		printf("check_lines[i]==%s", map->check_lines[i]);
		i++;
	}
	check_validity_map(map);
	return (0);
}
