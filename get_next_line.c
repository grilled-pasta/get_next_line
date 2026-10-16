/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 20:28:25 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/16 20:04:31 by alkonsta         ###   ########.fr       */
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
	static char	buff[BUFFER_SIZE + 1];
	char		*new_line;
	int			i;

	if (fd < 0)
		return (NULL);
	new_line = read_next_line(fd, buff);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if (new_line[i] == '\n' && new_line[i + 1])
	{
		i++;
		ft_bzero(buff, BUFFER_SIZE + 1);
		ft_memcpy(buff, new_line + i, ft_strlen(new_line + i) + 1);
		new_line[i] = '\0';
		new_line = ft_dupcat(new_line, NULL);
	}
	return (new_line);
}

// #include <stdio.h>
//
// int		main(void)
// {
// 	int		fd;
// 	char	*line;
//
// 	fd = open("README.md", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("~~%s~~", line);
// 		free(line);	
// 	}
// 	return (close(fd));
// }
