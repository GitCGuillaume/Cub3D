#include "../../includes/cub.h"
#include <stdio.h>

/*int	is_map_incorrect(int i, char *line, t_map *map)
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
}*/

int	is_line_correct(int i, char *line, t_map *map)
{
	if ((line[i] == 'R' && line[i + 1] == ' ')
		|| (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		|| (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		|| (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		|| (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		|| (line[i] == 'S' && line[i + 1] == ' '))
	{
		printf("0=%c", line[i]);
		printf("1=%c", line[i + 1]);
		return (1);
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
		i = i + 1;
		map->colour[3] = get_number_two(map, &i, line);
		if (line[i] == ',')
			map->colour[4] = get_number_two(map, &i, line);
		if (line[i] == ',')
			map->colour[5] = get_number_two(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
	}
	return (1);
}

char	*gnl_next_ft(t_map *map, char *tmp_line, char *join_str, char *line)
{
	char	*last_line;

	last_line = 0;
	if (check_indicator_full(map) < 8)
	{
		find_which_indicator(map, tmp_line);
		join_str = ft_strjoin(line, tmp_line);
		free(line);
		line = join_str;
		free(tmp_line);
		tmp_line = ft_strjoin(line, "|");
		free(line);
		last_line = tmp_line;
	}
	else
	{
		free(line);
		free(tmp_line);
		close_program_gnl(map, "Wrong number of parameter in map.\n", 2);
	}
	return (last_line);
}

char	*get_line_fd(t_map *map, int fd)
{
	char	*line;
	char	*tmp_line;
	int	ret;
	int	i;
	char *join_str;

	line = ft_strdup("");
	tmp_line = NULL;
	join_str = NULL;
	i = 0;
	while ((ret = get_next_line(fd, &tmp_line)) > 0)
	{
		i = 0;
		while (tmp_line[i] == ' ' || tmp_line[i] == '\t')
			i++;
		line = gnl_next_ft(map, tmp_line, join_str, line);
		/*if (check_indicator_full(map) < 8)
		{
			find_which_indicator(map, tmp_line);
			join_str = ft_strjoin(line, tmp_line);
			free(line);
			line = join_str;
			free(tmp_line);
			tmp_line = ft_strjoin(line, "|");
			free(line);
			line = tmp_line;
		}
		else
		{
			free(line);
			free(tmp_line);
			close_program_gnl(map, "Wrong number of parameter in map.\n", 2);
		}*/
	}
	printf("colour0=%s\n", map->colour[0]);
	printf("colour1=%s\n", map->colour[1]);
	printf("colour2=%s\n", map->colour[2]);
	printf("colour3=%s\n", map->colour[3]);
	printf("colour4=%s\n", map->colour[4]);
	printf("colour5=%s\n", map->colour[5]);
	printf("resolution0=%s\n", map->resolution[0]);
	printf("resolution1=%s\n", map->resolution[1]);
	free(tmp_line);
	return (line);
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
	int	is_space_ok;

	i = 0;
	is_space_ok = 0;
	printf("line===%s ???", map->full_line);
	is_space_ok = is_full_line_ok(map->full_line);
	 if (is_space_ok > 0)
		map->lines = ft_split(map->full_line, '|');
	else
		close_program_gnl(map, "Map parameters wrongs, or space between map lines are here, remove them.\n", 2);
	if (map->is_resolution != 2)
		close_program_gnl(map, "Resolution is invalid.\n", 2);
	if (map->colour_counter != 6)
		close_program_gnl(map, "Configurations map colour is wrong, check RGB inputs number.\n", 2);
	i = 0;
	while (map->lines[i])
	{
		printf("check_lines[i]==%s", map->lines[i]);
		i++;
	}
	check_validity_map(map);
	return (0);
}
