/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:35:47 by gchopin           #+#    #+#             */
/*   Updated: 2021/02/03 17:38:28 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

short int		is_full_line_ok(char *line)
{
	short int	is_ok;
	int	i;

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
		{
			is_ok = 0;
		}
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

void	find_texture_two(char *line, unsigned int i, t_map *map)
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

int	find_colour(char *line, unsigned int *i,
	unsigned int old_i, t_map *map)
{
	if (line[old_i] == 'F' && line[old_i + 1] == ' ')
	{
		map->colour[0] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[1] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[2] = get_number_two(map, i, line);
		if (line[*i] != '\0' || !map->colour[0] || !map->colour[1]
				|| !map->colour[2])
			return (0);
		ft_memset(line, 0, ft_strlen(line));
	}
	if (line[old_i] == 'C' && line[old_i + 1] == ' ')
	{
		map->colour[3] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[4] = get_number_two(map, i, line);
		if (line[*i] == ',')
			map->colour[5] = get_number_two(map, i, line);
		if (line[*i] != '\0' || !map->colour[3]
				|| !map->colour[4] || !map->colour[5])
			return (0);
		ft_memset(line, 0, ft_strlen(line));
	}
	return (1);
}
