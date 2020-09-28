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

int	get_resolutions(t_map *map, unsigned int *i, char *line)
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
	while (!is_tab(line[*i]) && !is_other(line[*i]) && line[*i] != '\0')
		(*i)++;
	end = *i;
	value = ft_atoi(ft_substr(line, start, end - start));
	if (map->is_resolution == 0 && value > 0)
		map->is_resolution = 1;
	else if (map->is_resolution == 1 && value > 0)
		map->is_resolution = 2;
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
		map->resolution[0] = get_resolutions(map, &i, line);
		map->resolution[1] = get_resolutions(map, &i, line);
		if (map->is_resolution != 2)
		{
			ft_putstr_fd("Resolution is not good (and add strerror too pls)", 2);
			exit(0);
		}
	}
	if (line[old_i] == 'N' && line[old_i + 1] == 'O')
		map->north_path = get_texture(map, old_i, line);
	else if (line[old_i] == 'S' && line[old_i + 1] == 'O')
		map->south_path = get_texture(map, old_i, line);
	else if (line[old_i] == 'W' && line[old_i + 1] == 'E')
		map->west_path = get_texture(map, old_i, line);
	else if (line[old_i] == 'E' && line[old_i + 1] == 'A')
		map->east_path = get_texture(map, old_i, line);
	printf("no=%s\n", map->north_path);
	printf("so=%s\n", map->south_path);
	printf("ea=%s\n", map->east_path);
	printf("we=%s\n", map->west_path);
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
	return (0);
}

int	parse_line_fd(t_map *map)
{
	map->lines = ft_split(map->full_line, '|');
	check_configuration(map);	
	return (0);
}
