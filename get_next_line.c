/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:42:09 by sel-hasn          #+#    #+#             */
/*   Updated: 2023/12/13 17:11:07 by sel-hasn         ###   ########.fr       */
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
		return (free(s), NULL);
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
	char	*str;

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
	str = ft_substr(s, i, j);
	if (!str)
		return (free(s), NULL);
	free (s);
	return (str);
}

char	*read_line(int fd, char *s)
{
	char	*buffer;
	ssize_t	x;

	if (!s)
	{
		s = ft_strdup("");
		if (!s)
			return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	x = 1;
	while (ft_newline(s) == 0 && x != 0)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x == -1)
			return (free(s), free(buffer), NULL);
		buffer[x] = '\0';
		s = ft_strjoin(s, buffer);
		if (!s)
			return (free(s), free(buffer), NULL);
	}
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*str;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	s = read_line(fd, s);
	if (!s)
		return (free(s), NULL);
	str = line(s);
	s = rest_of_str(s);
	return (str);
}
