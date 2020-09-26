/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:35:27 by gchopin           #+#    #+#             */
/*   Updated: 2020/09/07 11:03:17 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
char			*ft_strdup_gnl(const char *s1);
size_t	ft_len(char const *str);

#endif
