/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:25:08 by ykisibek          #+#    #+#             */
/*   Updated: 2024/03/17 18:25:09 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_line(char *line, int fd)
{
	char	*line_read;
	int		chars_read;

	line_read = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_read)
		return (NULL);
	chars_read = 1;
	while (!(ft_strchr(line, '\n')) && chars_read != 0)
	{
		chars_read = read(fd, line_read, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(line);
			line = NULL;
			free(line_read);
			line_read = NULL;
			return (NULL);
		}
		line_read[chars_read] = '\0';
		line = ft_strjoin(line, line_read);
	}
	free(line_read);
	line_read = NULL;
	return (line);
}

int	count_nl(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*free_from_nl(char *line)
{
	int		size;
	char	*left_line;
	int		i;
	int		j;

	if (!line || !(*line))
		return (NULL);
	i = count_nl(line);
	j = ft_strlen(line);
	size = j - i + 1;
	left_line = (char *)malloc(size * sizeof(char));
	if (!left_line)
		return (NULL);
	size--;
	while (size >= 0)
		left_line[size--] = line[j--];
	free(line);
	line = NULL;
	return (left_line);
}

char	*copy_with_nl(char *line)
{
	int		i;
	char	*send;

	if (!line || !(*line))
		return (NULL);
	send = (char *)malloc((count_nl(line) + 1) * sizeof(char));
	if (!send)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		send[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		send[i] = '\n';
		send[i + 1] = '\0';
	}
	else
		send[i] = '\0';
	return (send);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*line_to_send;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = fill_line(line[fd], fd);
	if (!line[fd])
		return (NULL);
	line_to_send = copy_with_nl(line[fd]);
	if (!line_to_send)
	{
		free (line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd] = free_from_nl(line[fd]);
	if (!line[fd])
		return (NULL);
	return (line_to_send);
}
