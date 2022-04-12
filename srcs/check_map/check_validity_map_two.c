/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_map_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:27:42 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/12 09:55:57 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	check_indicator_full(t_map *map)
{
	int	i;

	i = 0;
	if (map->is_north == 1)
		i++;
	if (map->is_south == 1)
		i++;
	if (map->is_east == 1)
		i++;
	if (map->is_west == 1)
		i++;
	if (map->colour_counter == 6)
		i++;
	//if (map->is_resolution == 2)
	//	i++;
	return (i);
}

unsigned int	check_first_character(t_map *map)
{
	unsigned int	i;

	i = 0;
	if (map->lines)
	{
		while (map->lines[i] && (map->lines[i][0] != '0'
			&& map->lines[i][0] != '1'
			&& map->lines[i][0] != 'N'
			&& map->lines[i][0] != 'S' && map->lines[i][0] != 'E'
			&& map->lines[i][0] != 'W' && map->lines[i][0] != ' '))
		{
			i++;
		}
		if (map->lines[i] && (map->lines[i][0] == '0' || map->lines[i][0] == '1'
			|| map->lines[i][0] == 'N'
			|| map->lines[i][0] == 'S' || map->lines[i][0] == 'E'
			|| map->lines[i][0] == 'W' || map->lines[i][0] == ' '))
			return (i);
	}
	return (0);
}

static int	case_is_false(char *line, unsigned int j)
{
	if (line)
	{
		if (line[j] != '\0' && (line[j] != '1'
				&& line[j] != 'N'
				&& line[j] != 'S' && line[j] != 'E'
				&& line[j] != 'W' && line[j] != '0'
				&& line[j] != ' '))
		{
			return (1);
		}
	}
	return (0);
}

static unsigned int	check_character(char *character)
{
	unsigned int	j;

	j = 0;
	if (character)
	{
		while (character[j] != '\0'
			&& (character[j] == '0' || character[j] == '1'
				|| character[j] == 'N'
				|| character[j] == 'S' || character[j] == 'E'
				|| character[j] == 'W' || is_space(character[j])
				|| character[j] == ' '))
		{
			j++;
		}
	}
	return (j);
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
			j = check_character(map->lines[i]);
			if (case_is_false(map->lines[i], j) == 1)
				close_program_gnl(map, "Bad character in map game.\n", 2);
			i++;
		}
	}
	return (0);
}
