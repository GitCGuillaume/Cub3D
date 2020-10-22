#include "../includes/cub.h"

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
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			is_ok = 0;
		i++;
	}
	return (is_ok);
}

void	is_printable(t_map *map, char *line, unsigned int *i)
{
		while (line[*i] != ' ' && line[*i] != '\0')
			(*i)++;
		while (line[*i] == ' ' && line[*i] != '\0')
			(*i)++;
		if (!ft_isprint(line[*i]))
		{
			free(line);
			close_program_gnl(map, "An error occured.", 2);
		}
}

void find_texture_three(char *line, unsigned int i, t_map *map)
{
	if (line[i] == 'E' && line[i + 1] == 'A'
			&& line[i + 2] == ' ' && map->is_east == 0)
	{
		map->east_path = get_texture(map, i, line);
		map->is_east++;
	}
	if (line[i] == 'S' && line[i + 1] == ' '
			&& map->is_sprite == 0)
	{
		map->sprite_path = get_texture(map, i, line);
		map->is_sprite++;
	}

}
