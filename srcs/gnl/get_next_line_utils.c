/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:36:16 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/11 15:56:36 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_g(const char *s1)
{
	char	*ptr_char;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[j] != '\0' && s1[j] != '\n')
			j++;
	}
	else
	{
		return (NULL);
	}
	ptr_char = malloc(j + 1);
	if (ptr_char == NULL)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		*(ptr_char + i) = s1[i];
		i++;
	}
	*(ptr_char + i) = '\0';
	return (ptr_char);
}

char	*ft_substr_g(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = malloc((sizeof(char) * len) + 1);
	if (ptr == NULL)
		return (NULL);
	if (ft_len(s) < start)
	{
		ptr[i] = '\0';
		return (ptr);
	}
	while (len > i && s[start] != '\0')
	{
		ptr[i] = (char)s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
