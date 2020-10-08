#include "../../includes/cub.h"
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
		printf("tmp=%d ", tmp_line[0]);
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
	find_texture(line, old_i, map);
	find_texture_two(line, &i, old_i, map);
	if (line[old_i] == 'C' && (is_tab(line[old_i + 1]) || is_other(line[old_i + 1])))
	{
		map->colour[3] = get_number_two(map, &i, line);
		map->colour[4] = get_number_two(map, &i, line);
		map->colour[5] = get_number_two(map, &i, line);
		ft_memset(line, 0, ft_strlen(line));
	}
	return (0);
}

int	is_lines_incorrect(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\n");
	while (map->lines[i])
	{
		j = 0;
		printf("line=%s\n", map->lines[i]);
		printf("line=%c\n", map->lines[i][j]);
		printf("line=%d\n", map->lines[i][j + 1]);
		//while (is_tab(map->lines[i][j]) && is_other(map->lines[i][j])
		//	&& map->lines[i][j] != '\0')
		//	j++;
		if ((map->lines[i][j] != 'R' && map->lines[i][j + 1] != ' ')
			&& (map->lines[i][j] != 'N' && map->lines[i][j + 1] != 'O')
			&& (map->lines[i][j] != 'S' && map->lines[i][j + 1] != 'O')
			&& (map->lines[i][j] != 'W' && map->lines[i][j + 1] != 'E')
			&& (map->lines[i][j] != 'E' && map->lines[i][j + 1] != 'A')
			&& (map->lines[i][j] != 'S' && map->lines[i][j + 1] != ' '))
		{
			printf("ALLLOOO");
			return (1);
		}
		i++;
	}
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
	if (map->colour_counter != 6)
	{
		close_program(map, "Configurations map colour is wrong, check RGB inputs number.\n", 2);
	}
	return (0);
}
#include <stdio.h>
int	parse_line_fd(t_map *map)
{
	map->lines = ft_split(map->full_line, '|');
	map->check_lines = ft_split(map->full_line, '|');
	if (is_lines_incorrect(map) == 1)
		close_program(map, "Configuration file is incorrect.\n", 2);
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
