/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:22:52 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 09:56:59 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_array(char **ptr)
{
	int	size;

	size = 0;
	if (ptr)
	{
		while (ptr[size] != NULL)
			size++;
		while (size != 0)
		{
			size--;
			if (ptr[size])
				free(ptr[size]);
		}
		free(ptr);
	}
}
