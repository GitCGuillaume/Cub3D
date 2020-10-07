#include "../includes/cub.h"

#include <stdio.h>
char	*get_line_fd(int fd)
{
	char	*line;
	char	*tmp_line;
	char	*join_str;
	int	ret;
	
	line = NULL;
	tmp_line = NULL;
	join_str = NULL;
	if (!(line = malloc(sizeof(char))))
		return (NULL);
	line[0] = '\0';
	while ((ret = get_next_line(fd, &tmp_line)) > 0)
	{
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

int	find_which_indicator(t_map *map, char *line)
{
	unsigned int	i;
	unsigned int	old_i;

	i = 0;
	while (is_tab(line[i]) || is_other(line[i]))
		i++;
	old_i = i;
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		map->resolution[0] = get_number(map, &i, line);
		map->resolution[1] = get_number(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
		if (map->is_resolution == 0 && map->resolution[0][0] != '\0')
			map->is_resolution = 1;
		if (map->is_resolution == 1 && map->resolution[1][0] != '\0')
			map->is_resolution = 2;
		if (map->is_resolution != 2)
		{
			ft_putstr_fd("Resolution is not good (and add strerror too pls)", 2);
			exit(0);
		}
	}
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
	if (line[old_i] == 'F' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->colour[0] = get_number_two(map, &i, line);
		map->colour[1] = get_number_two(map, &i, line);
		map->colour[2] = get_number_two(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
		printf("map->col1 %s\n", map->colour[0]);
		printf("map->col2 %s\n", map->colour[1]);
		printf("map->col3 %s\n", map->colour[2]);
		printf("colour_counter=%d\n", map->colour_counter);
	}
	if (line[old_i] == 'C' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->colour[3] = get_number_two(map, &i, line);
		map->colour[4] = get_number_two(map, &i, line);
		map->colour[5] = get_number_two(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
		printf("map->col3 %s\n", map->colour[3]);
		printf("map->col4 %s\n", map->colour[4]);
		printf("map->col5 %s\n", map->colour[5]);
		printf("colour_counter=%d\n", map->colour_counter);
	}
	printf("no=%s\n", map->north_path);
	printf("so=%s\n", map->south_path);
	printf("ea=%s\n", map->east_path);
	printf("we=%s\n", map->west_path);
	printf("sprite=%s\n", map->sprite_path);
	return (0);
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
	if (map->colour_counter < 6)
	{
		ft_putstr_fd("You must enter 6 colours number (and add strerror too pls)", 2);
		exit(0);
	}
	return (0);
}

int	parse_line_fd(t_map *map)
{
	map->lines = ft_split(map->full_line, '|');
	map->check_lines = ft_split(map->full_line, '|');
	check_configuration(map);	
	int i = 0;
	while (map->lines[i])
	{
		printf("l=%s\n", map->lines[i]);
		i++;
	}
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
	check_validity_map(map);
	return (0);
}
