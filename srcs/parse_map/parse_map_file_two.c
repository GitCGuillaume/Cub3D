#include "../../includes/cub.h"

char	*get_number(t_map *map, unsigned int *i, char *line)
{
	unsigned int	start;
	unsigned int	end;
	char		*value;

	start = 0;
	end = 0;
	value = 0;
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	while (!is_tab(line[*i]) && !is_other(line[*i])
		&& line[*i] != '\0' && ft_isdigit(line[*i]))
		(*i)++;
	end = *i;
	value = ft_substr(line, start, end - start);
	return (value);
}

char	*get_number_two(t_map *map, unsigned int *i, char *line)
{
	unsigned int	start;
	char	*value;

	start = 0;
	value = 0;
	(*i)++;
	if (line[*i] == ',')
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	if (ft_isdigit(line[*i]))
		map->colour_counter = map->colour_counter + 1;
	while (!is_tab(line[*i]) && !is_other(line[*i])
		&& line[*i] != '\0' && ft_isdigit(line[*i]))
		(*i)++;
	value = ft_substr(line, start, *i - start);
	return (value);
}

char	*get_texture(t_map *map, unsigned int i, char *line)
{
	unsigned int	start;
	unsigned int	end;
	char		*value;

	start = 0;
	end = 0;
	value = 0;
	is_printable(map, line, &i);
	start = i;
	while (line[i] != '\0')
		i++;
	end = i;
	value = ft_substr(line, start, end - start);
	ft_memset(line, 0, ft_strlen(line));
	return (value);
}

void	find_texture_two(char *line, unsigned int *i,
	unsigned int old_i, t_map *map)
{
	if (line[*i] == 'R' && line[*i + 1] == ' ')
	{
		map->resolution[0] = get_number(map, i, line);
		map->resolution[1] = get_number(map, i, line);
		ft_memset(line, 0, ft_strlen(line));
		if (map->is_resolution == 0 && map->resolution[0][0] != '\0')
			map->is_resolution = 1;
		if (map->is_resolution == 1 && map->resolution[1][0] != '\0')
			map->is_resolution = 2;
	}
	if (line[old_i] == 'F' && line[old_i + 1] == ' ')
	{
		*i = *i + 1;
		map->colour[0] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[1] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[2] = get_number_two(map, i, line);
		ft_memset(line, 0, ft_strlen(line));
	}
}

void	find_texture(char *line, unsigned int i, t_map *map)
{
	if (line[i] == 'N' && line[i + 1] == 'O'
			&& line[i + 2] == ' ' && map->is_north == 0)
	{
		map->north_path = get_texture(map, i, line);
		map->is_north++;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O'
			&& line[i + 2] == ' ' && map->is_south == 0)
	{
		map->south_path = get_texture(map, i, line);
		map->is_south++;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E'
			&& line[i + 2] == ' ' && map->is_west == 0)
	{
		map->west_path = get_texture(map, i, line);
		map->is_west++;
	}
	find_texture_three(line, i, map);
}
