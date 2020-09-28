#include "../includes/cub.h"

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
#include <stdio.h>

static int		is_tab(char c)
{
	if (c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

static int		is_other(char c)
{
	if (c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

int	get_number(t_map *map, unsigned int *i, char *line)
{
	unsigned int	start;
	unsigned int	end;
	int		value;

	start = 0;
	end = 0;
	value = 0;
	while (line[*i] != '\0' && !ft_isdigit(line[*i]))
		(*i)++;
	start = *i;
	while (!is_tab(line[*i]) && !is_other(line[*i]) && line[*i] != '\0' && ft_isdigit(line[*i]))
		(*i)++;
	end = *i;
	value = ft_atoi(ft_substr(line, start, end - start));
	return (value);
}
int	get_number_two(t_map *map, unsigned int *i, char *line)
{
	unsigned int	start;
	unsigned int	end;
	int		value;
	int		rgb_found;

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
	value = ft_atoi(ft_substr(line, start, end - start));
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
	while (!is_tab(line[i]) && !is_other(line[i]) && line[i] != '\0')
		i++;
	while ((is_tab(line[i]) || is_other(line[i]))==1 && line[i] != '\0')
		i++;
	start = i;
	while (line[i] != '\0')
		i++;
	end = i;
	return (ft_substr(line, start, end - start));
}

int	find_which_indicator(t_map *map, char *line)
{
	unsigned int	i;
	unsigned int	old_i;
	char		*string;

	i = 0;
	string = NULL;
	while (is_tab(line[i]) || is_other(line[i]))
		i++;
	old_i = i;
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		map->resolution[0] = get_number(map, &i, line);
		if (map->is_resolution == 0 && map->resolution > 0)
			map->is_resolution = 1;
		map->resolution[1] = get_number(map, &i, line);
		if (map->is_resolution == 1 && map->resolution > 0)
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
		printf("map->col1 %d\n", map->colour[0]);
		printf("map->col2 %d\n", map->colour[1]);
		printf("map->col3 %d\n", map->colour[2]);
		printf("colour_counter=%d\n", map->colour_counter);
	}
	if (line[old_i] == 'C' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->colour[3] = get_number_two(map, &i, line);
		map->colour[4] = get_number_two(map, &i, line);
		map->colour[5] = get_number_two(map, &i, line);
		printf("map->col3 %d\n", map->colour[3]);
		printf("map->col4 %d\n", map->colour[4]);
		printf("map->col5 %d\n", map->colour[5]);
		printf("colour_counter=%d\n", map->colour_counter);
	}
	printf("no=%s\n", map->north_path);
	printf("so=%s\n", map->south_path);
	printf("ea=%s\n", map->east_path);
	printf("we=%s\n", map->west_path);
	printf("sprite=%s\n", map->sprite_path);
	free(string);
	return (0);
}

int	check_configuration(t_map *map)
{
	int	i;
	int	j;
	//char	*indicators;

	i = 0;
	j = 0;
	//indicators = ft_strdup("R;NO;SO;WE;EA;S;F;C");
	while (map->lines[i])
	{
		find_which_indicator(map, map->lines[i]);
		i++;
	}
	printf("colour number is =%d", map->colour_counter);
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

	check_configuration(map);	
	return (0);
}
