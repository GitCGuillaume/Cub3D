/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:35:16 by gchopin           #+#    #+#             */
/*   Updated: 2020/07/30 13:16:59 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		clear_memory(char **str, char **str_two, int type)
{
	size_t i;

	i = 0;
	if (str && type == 1)
	{
		free(*str);
		*str = NULL;
	}
	while (str_two != 0 && 10241 > i)
	{
		if (str && type == 0)
		{
			free(str[i]);
			str[i] = NULL;
		}
		if (str_two)
		{
			free(str_two[i]);
			str_two[i] = NULL;
		}
		i++;
	}
	return (-1);
}

int		len_n(char *str, int *res)
{
	size_t i;

	i = 0;
	if (str)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
		{
			*res = 1;
			i++;
		}
	}
	return (i);
}

int		get_last_n(char **line, char **m_ln, int *res, int fd)
{
	char	*m_tmp;

	if (!m_ln[fd] || m_ln[fd][0] == '\0')
	{
		if (!(m_tmp = ft_substr(*line, 0, ft_len(*line))))
			return (clear_memory(line, 0, 1));
	}
	else
	{
		if (!(m_tmp = ft_substr(m_ln[fd], 0, ft_len(m_ln[fd]))))
			return (clear_memory(line, m_ln, 1));
	}
	free(m_ln[fd]);
	m_ln[fd] = m_tmp;
	if (!(m_tmp = ft_strdup_gnl(m_ln[fd])))
		return (clear_memory(line, m_ln, 1));
	free(*line);
	*line = m_tmp;
	if (!(m_tmp = ft_substr(m_ln[fd], len_n(m_ln[fd], res), ft_len(m_ln[fd]))))
		return (clear_memory(line, m_ln, 1));
	free(m_ln[fd]);
	m_ln[fd] = m_tmp;
	if (m_ln[fd][0] == 0 || *res == -1 || *res == 0)
		clear_memory(&m_ln[fd], 0, 1);
	return (*res);
}

int		read_line(int fd, char **line, char **mem_line)
{
	char	buff[10241];
	char	*tmp;
	int		ret;

	free(*line);
	if (!(*line = malloc(sizeof(char))))
		return (-1);
	*line[0] = '\0';
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(*line, buff);
		if (tmp == NULL)
			return (clear_memory(line, 0, 1));
		free(*line);
		*line = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		return (clear_memory(line, mem_line, 1));
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*m_line[10241];
	char		*mem_tmp;
	int			res;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (m_line[fd] && m_line[fd][0] != 0 && ft_strchr(m_line[fd], '\n') != 0)
		return (get_last_n(line, m_line, &res, fd));
	res = read_line(fd, line, m_line);
	if (res != -1)
	{
		if (m_line[fd] && m_line[fd][0] != 0 && !ft_strchr(m_line[fd], '\n'))
		{
			if (!(mem_tmp = ft_strjoin(m_line[fd], *line)))
				return (clear_memory(line, m_line, 1));
			free(m_line[fd]);
			m_line[fd] = mem_tmp;
		}
		res = get_last_n(line, m_line, &res, fd);
	}
	return (res);
}
