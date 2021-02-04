/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:31:43 by gchopin           #+#    #+#             */
/*   Updated: 2021/02/04 18:30:10 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int		find_which_indicator(t_map *map, char *line)
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
		map->fd = ft_close_fd(map->fd);
		close_program_gnl(map, "Wrong number of parameter in map.\n", 2);
	}
	return (last_line);
}

char	*get_line_fd(t_map *map, int fd)
{
	char	*line;
	char	*tmp_line;
	char	*join_str;
	int		ret;
	int		i;

	line = ft_strdup("");
	tmp_line = NULL;
	i = 0;
	join_str = NULL;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &tmp_line);
		i = 0;
		while (tmp_line[i] == ' ' || tmp_line[i] == '\t')
			i++;
		line = gnl_next_ft(map, tmp_line, join_str, line);
	}
	free(tmp_line);
	return (line);
}

int		parse_line_fd(t_map *map)
{
	int	i;
	int	is_space_ok;

	i = 0;
	is_space_ok = 0;
	is_space_ok = is_full_line_ok(map->full_line);
	if (is_space_ok > 0)
	{
		map->lines = ft_split(map->full_line, '|');
		map->lines_copy = ft_split(map->full_line, '|');
	}
	else
		close_program_gnl(map,
				"Map parameters wrongs, or remove space in map fields.\n", 2);
	if (map->is_resolution != 2)
		close_program_gnl(map, "Resolution is invalid.\n", 2);
	if (map->colour_counter != 6)
		close_program_gnl(map, "Check RGB inputs number.\n", 2);
	i = 0;
	while (map->lines[i])
		i++;
	check_validity_map(map);
	return (0);
}
