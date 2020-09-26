/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:36:16 by gchopin           #+#    #+#             */
/*   Updated: 2020/07/28 23:36:18 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*ptr_char;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[j] != '\0' && s1[j] != '\n')
		j++;
	if (!(ptr_char = malloc(j + 1)))
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		*(ptr_char + i) = s1[i];
		i++;
	}
	*(ptr_char + i) = '\0';
	return (ptr_char);
}
