/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:03:56 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/16 20:04:46 by alkonsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char *buff)
{
	int		bytes;
	char	*new_line;

	new_line = NULL;
	if (ft_strlen(buff) > 0)
	{
		new_line = ft_dupcat(NULL, buff);
		ft_bzero(buff, BUFFER_SIZE + 1);
		if (!new_line)
			return (NULL);
	}
	while (!contains_new_line(new_line))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_bzero(buff, BUFFER_SIZE + 1), free(new_line), NULL);
		if (bytes == 0)
			return (ft_bzero(buff, BUFFER_SIZE + 1), new_line);
		buff[bytes] = '\0';
		new_line = ft_dupcat(new_line, buff);
		ft_bzero(buff, BUFFER_SIZE + 1);
		if (!new_line)
			return (NULL);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char		*new_line;
	int			i;

	if (fd < 0)
		return (NULL);
	new_line = read_next_line(fd, buff[fd]);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if (new_line[i] == '\n' && new_line[i + 1])
	{
		i++;
		ft_bzero(buff[fd], BUFFER_SIZE + 1);
		ft_memcpy(buff[fd], new_line + i, ft_strlen(new_line + i) + 1);
		new_line[i] = '\0';
		new_line = ft_dupcat(new_line, NULL);
	}
	return (new_line);
}
