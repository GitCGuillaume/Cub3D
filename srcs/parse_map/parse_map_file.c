/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:31:43 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/12 13:38:30 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	find_which_indicator(t_map *map, char **line)
{
	unsigned int	i;
	unsigned int	old_i;
	int				result;

	i = 0;
	result = 0;
	if (line)
	{
		while (is_tab(*line[i]) || is_other(*line[i]))
			i++;
		old_i = i;
		if (*line[old_i] == 'C' || *line[old_i] == 'F')
			i++;
		find_texture(*line, old_i, map);
		if (line && *line)
			result = find_colour(*line, &i, old_i, map);
	}
	if (result == 0)
	{
		free(*line);
		*line = NULL;
		close_program(map,
			"Ceiling/floor colour bad format or line wrong.\n", 2);
	}
}

char	*gnl_next_ft(t_map *map, char *tmp_line, char *join_str)
{
	char	*last_line;

	last_line = NULL;
	if (check_indicator_full(map) < 6)
	{
		find_which_indicator(map, &tmp_line);
		if (tmp_line)
			last_line = ft_strjoin(join_str, tmp_line);
		free(join_str);
		free(tmp_line);
		if (last_line == NULL)
			close_program(map, "An error occured while reading the map.\n", 2);
		tmp_line = ft_strjoin(last_line, "|");
		free(last_line);
		if (tmp_line == NULL)
			close_program(map, "An error occured while reading the map.\n", 2);
		last_line = tmp_line;
	}
	else
	{
		if (tmp_line)
			free(tmp_line);
		close_program(map, "Wrong number of parameter in map.\n", 2);
	}
	return (last_line);
}

void	get_line_fd(t_map *map, int fd)
{
	char	*tmp_line;
	int		ret;
	int		i;

	map->full_line = ft_strdup("");
	if (map->full_line == NULL)
		close_program(map, "Engine error.\n", 2);
	tmp_line = NULL;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &tmp_line);
		if (tmp_line == NULL)
			close_program_gnl(map, "Engine returned no map.\n", 2);
		if (ret > 0)
		{
			i = 0;
			while (tmp_line && (tmp_line[i] == ' ' || tmp_line[i] == '\t'))
				i++;
			map->full_line = gnl_next_ft(map, tmp_line, map->full_line);
		}
	}
	free(tmp_line);
}

int	parse_line_fd(t_map *map)
{
	short int	is_space_ok;

	is_space_ok = 0;
	is_space_ok = is_full_line_ok(map->full_line);
	if (is_space_ok > (short int)0)
	{
		map->lines = ft_split(map->full_line, '|');
		map->lines_copy = ft_split(map->full_line, '|');
	}
	else
		close_program_gnl(map,
			"Map parameters wrongs, or remove space in map fields.\n", 2);
	if (map->colour_counter != 6)
		close_program_gnl(map, "Check RGB inputs number.\n", 2);
	if (map->lines == NULL)
	{
		free_array(map->lines_copy);
		close_program(map, "Couldn't register lines.\n", 2);
	}
	check_validity_map(map);
	return (0);
}
