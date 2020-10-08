#include "../../includes/cub.h"

static int	check_first_character(t_map *map)
{
	unsigned int	i;

	i = 0;
	if (map->lines)
	{
		while (map->lines[i] && (map->lines[i][0] != '0'
			&& map->lines[i][0] != '1'
			&& map->lines[i][0] != '2' && map->lines[i][0] != 'N'
			&& map->lines[i][0] != 'S' && map->lines[i][0] != 'E'
			&& map->lines[i][0] != 'W'))
		{
			i++;
		}
		if (map->lines[i] && (map->lines[i][0] == '0' || map->lines[i][0] == '1'
			|| map->lines[i][0] == '2' || map->lines[i][0] == 'N'
			|| map->lines[i][0] == 'S' || map->lines[i][0] == 'E'
			|| map->lines[i][0] == 'W'))
			return (i);
	}
	return (0);
}

static int	case_is_false(char *line, unsigned int j)
{
	if (line[j] != '\0' && (line[j] != '1'
		&& line[j] != '2' && line[j] != 'N'
		&& line[j] != 'S' && line[j] != 'E'
		&& line[j] != 'W' && line[j] != '0'
		&& !is_space(line[j])))
	{
		return (1);
	}
	return (0);
}

int	check_valid_character(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	i = check_first_character(map);
	if (map->lines)
	{
		while (map->lines[i])
		{
			j = 0;
			while (map->lines[i][j] != '\0' &&
				(map->lines[i][j] == '0' || map->lines[i][j] == '1'
				|| map->lines[i][j] == '2' || map->lines[i][j] == 'N'
				|| map->lines[i][j] == 'S' || map->lines[i][j] == 'E'
				|| map->lines[i][j] == 'W' || is_space(map->lines[i][j])))
			{
				j++;
			}
			if (case_is_false(map->lines[i], j) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}
