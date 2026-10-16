/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 20:28:25 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/09 22:18:25 by alkonsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stddef.h>

char	*read_next_line(int fd, char *buff)
{
	int		bytes;
	char	*new_line;
	char	*temp;

	new_line = NULL;
	if (ft_strlen(buff) > 0)
	{
		new_line = ft_dupcat(NULL, buff);
		ft_strzero(buff);
		if (!new_line)
			return (NULL);
	}
	while (!contains_new_line(new_line))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_strzero(buff), free(new_line), NULL);
		if (bytes == 0)
			return (ft_strzero(buff), new_line);
		buff[bytes] = '\0';
		temp = new_line;
		new_line = ft_dupcat(new_line, buff);
		free(temp);
		ft_strzero(buff);
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
	char		*temp;

	if (fd < 0)
		return (NULL);
	new_line = read_next_line(fd, buff);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if (new_line[i] == '\n')
	{
		i++;
		ft_strzero(buff);
		ft_memcpy(buff, new_line + i, ft_strlen(new_line + i) + 1);
		new_line[i] = '\0';
		temp = new_line;
		new_line = ft_dupcat(new_line, NULL);
		free(temp);
	}
	return (new_line);
}

// int		main(void)
// {
// 	int		fd;
// 	char	*line;
//
// 	// fd = open("multinewlines.txt", O_RDONLY);
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
