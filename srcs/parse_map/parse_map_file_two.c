#include "../../includes/cub.h"

char	*get_number(t_map *map, unsigned int *i, char *line)
{
	unsigned int	start;
	unsigned int	end;
	char		*value;

	start = 0;
	end = 0;
	value = 0;
	while (line[*i] != '\0' && !ft_isdigit(line[*i]))
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
	unsigned int	end;
	int		rgb_found;
	char		*value;

	start = 0;
	end = 0;
	value = 0;
	rgb_found = 0;
	while (line[*i] != '\0' && !ft_isdigit(line[*i]))
		(*i)++;
	start = *i;
	while (!is_tab(line[*i]) && !is_other(line[*i])
		&& line[*i] != '\0' && ft_isdigit(line[*i]))
	{
		rgb_found++;
		(*i)++;
	}
	end = *i;
	value = ft_substr(line, start, end - start);
	if (rgb_found > 0)
		map->colour_counter = map->colour_counter + 1;
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
	while (!is_tab(line[i]) && !is_other(line[i])
		&& line[i] != '\0')
		i++;
	while ((is_tab(line[i]) || is_other(line[i]))== 1
		&& line[i] != '\0')
		i++;
	start = i;
	while (line[i] != '\0')
		i++;
	end = i;
	value = ft_substr(line, start, end - start);
	ft_memset(line, 0, ft_strlen(line));
	return (value);
}

void	find_texture_two(char *line, unsigned int *i, unsigned int old_i, t_map *map)
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
		if (map->is_resolution != 2)
		{
			close_program(map, "Resolution is invalid.\n", 2);
		}
	}
	if (line[old_i] == 'F' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->colour[0] = get_number_two(map, i, line);
		map->colour[1] = get_number_two(map, i, line);
		map->colour[2] = get_number_two(map, i, line);
		ft_memset(line, 0, ft_strlen(line));
	}
}

void	find_texture(char *line, unsigned int old_i, t_map *map)
{
	if (line[old_i] == 'N' && line[old_i + 1] == 'O')
	{
		map->north_path = get_texture(map, old_i, line);
		map->is_north = 1;
	}
	else if (line[old_i] == 'S' && line[old_i + 1] == 'O')
	{
		map->south_path = get_texture(map, old_i, line);
		map->is_south = 1;
	}
	else if (line[old_i] == 'W' && line[old_i + 1] == 'E')
	{
		map->west_path = get_texture(map, old_i, line);
		map->is_west = 1;
	}
	else if (line[old_i] == 'E' && line[old_i + 1] == 'A')
	{
		map->east_path = get_texture(map, old_i, line);
		map->is_east = 1;
	}
	if (line[old_i] == 'S' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->sprite_path = get_texture(map, old_i, line);
		map->is_sprite = 1;
	}
}

