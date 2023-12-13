/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:42:09 by sel-hasn          #+#    #+#             */
/*   Updated: 2023/12/13 17:25:35 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	if (s[0] == '\0')
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rest_of_str(char *s)
{
	int		i;
	int		j;
	char	*rst;

	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (free(s), NULL);
	if (s[i] == '\n')
		i++;
	while (s[i + j] != '\0')
		j++;
	rst = ft_substr(s, i, j);
	if (!rst)
		return (NULL);
	free(s);
	return (rst);
}

char	*read_line(char *s, int fd)
{
	char	*buffer;
	ssize_t	y;

	if (!s)
	{
		s = ft_strdup("");
		if (!s)
			return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	y = 1;
	while (ft_newline(s) == 0 && y != 0)
	{
		y = read(fd, buffer, BUFFER_SIZE);
		if (y == -1)
			return (free(s), free(buffer), NULL);
		buffer[y] = '\0';
		s = ft_strjoin(s, buffer);
		if (!s)
			return (free(s), free(buffer), NULL);
	}
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	static char		*s;
	char			*str;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	s = read_line(s, fd);
	if (!s)
		return (NULL);
	str = line(s);
	s = rest_of_str(s);
	return (str);
}
