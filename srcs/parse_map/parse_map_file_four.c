/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_four.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:39:25 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:39:27 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_line_wrong(const char *line)
{
	unsigned int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] != 0 && line[i] != ' ' && line[i] != '1'
				&& line[i] != '0' && line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'E' && line[i] != 'W')
			{
				return (0);
			}
			i++;
		}
	}
	return (1);
}
