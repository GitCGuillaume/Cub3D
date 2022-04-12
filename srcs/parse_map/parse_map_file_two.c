/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:32:41 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/12 13:38:12 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*get_number(unsigned int *i, char *line)
{
	char			*value;
	unsigned int	start;
	unsigned int	end;

	start = 0;
	end = 0;
	value = NULL;
	(*i)++;
	if (line)
	{
		while (line[*i] && line[*i] == ' ')
			(*i)++;
		start = *i;
		while (!is_tab(line[*i]) && !is_other(line[*i])
			&& line[*i] != '\0' && ft_isdigit(line[*i]))
			(*i)++;
		end = *i;
		value = ft_substr(line, start, end - start);
	}
	return (value);
}

char	*get_number_two(t_map *map, unsigned int *i, char *line)
{
	char			*value;
	unsigned int	start;

	start = 0;
	value = NULL;
	(*i)++;
	if (line)
	{
		if (line[*i] == ',')
			(*i)++;
		while (line[*i] && line[*i] == ' ')
			(*i)++;
		start = *i;
		if (ft_isdigit(line[*i]))
			map->colour_counter = map->colour_counter + 1;
		while (!is_tab(line[*i]) && !is_other(line[*i])
			&& line[*i] != '\0' && ft_isdigit(line[*i]))
			(*i)++;
		value = ft_substr(line, start, *i - start);
	}
	return (value);
}

char	*get_texture(t_map *map, unsigned int i, char *line)
{
	char			*value;
	unsigned int	start;
	unsigned int	end;

	start = 0;
	end = 0;
	value = NULL;
	if (line)
	{
		is_printable(map, line, &i);
		start = i;
		while (line[i] != '\0')
			i++;
		end = i;
		value = ft_substr(line, start, end - start);
		ft_memset(line, 0, ft_strlen(line));
	}
	return (value);
}
/*
int	find_resolution(char *line, unsigned int *i, t_map *map)
{
	if (line)
	{
		if (line[*i] == 'R' && line[*i + 1] == ' ')
		{
			map->resolution[0] = get_number(i, line);
			map->resolution[1] = get_number(i, line);
			if (!line || line[*i] != '\0' || !map->resolution[0]
				|| !map->resolution[1])
				return (0);
			ft_memset(line, 0, ft_strlen(line));
			if (map->is_resolution == 0 && map->resolution[0][0] != '\0')
				map->is_resolution = 1;
			if (map->is_resolution == 1
				&& map->resolution[0][0] != '\0'
				&& map->resolution[1][0] != '\0')
				map->is_resolution = 2;
		}
	}
	return (1);
}
*/

void	find_texture(char *line, unsigned int i, t_map *map)
{
	if (line)
	{
		if (line[i] == 'N' && line[i + 1] == 'O'
			&& line[i + 2] == ' ' && map->is_north == 0)
		{
			map->north_path = get_texture(map, i, line);
			if (map->north_path != NULL)
				map->is_north++;
		}
		else if (line[i] == 'S' && line[i + 1] == 'O'
			&& line[i + 2] == ' ' && map->is_south == 0)
		{
			map->south_path = get_texture(map, i, line);
			if (map->south_path != NULL)
				map->is_south++;
		}
		else if (line[i] == 'W' && line[i + 1] == 'E'
			&& line[i + 2] == ' ' && map->is_west == 0)
		{
			map->west_path = get_texture(map, i, line);
			if (map->west_path != NULL)
				map->is_west++;
		}
	}
	find_texture_two(line, i, map);
}
