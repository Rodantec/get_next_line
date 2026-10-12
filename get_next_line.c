/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:27 by rodantec          #+#    #+#             */
/*   Updated: 2026/10/12 11:46:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_isnewline(int fd)
{
	int		bytes_read;
	char	*buffer;
	char	*line;
	char	*new_line;
	
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	line = ft_strdup("");
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		new_line = ft_strjoin(line, buffer);
		free(line);
		free(buffer);
		if (!new_line)
		{
			free(line);
			return (NULL);
		}
		line = new_line;
		if (ft_strchr(buffer, '\n'))
			break ;
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if(!buffer)
			return NULL;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_extract(char **stash)
{
	int		i;
	char	*line;
	char	*new_stash;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1 + ((*stash)[i] == '\n')));
	if (!line)
		return (NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
	{
		line[i] = (*stash)[i];
		i++;
	}
	if ((*stash)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	new_stash = ft_strdup(*stash + i);
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*gnl(int fd)
{
	static char	*stash;
	char		*line;
	char		*tmp;

	if (!stash)
		stash = ft_strdup("");
	tmp = ft_isnewline(fd);
	if (!tmp)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_strjoin(stash, tmp);
	free(tmp);
	free(stash);
	stash = line;
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_extract(&stash);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;


	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = gnl(fd);
	return (line);
}


