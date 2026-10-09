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

int		contains_new_line(char *s)
{
	while (*s && *s != '\n')
		s++;
	return (*s == '\n');
}

char	*get_next_line(int fd)
{
	int			bytes;
	int			buff_size;
	char		*buff;
	int			i;

	buff_size = 10;
	buff = (char *) malloc(sizeof(char) * buff_size + 1);
	bytes = read(fd, buff, buff_size);
	while (bytes > 0)
	{		
		if (contains_new_line(buff))
		{
			i = 0;
			while (buff[i])
			{
				if (buff[i] == '\n' && buff[i + 1])
				{
					buff[i + 1] = '\0';
					break ;
				}
				i++;
			}
			printf("%s", buff);
			return (buff);
		}
		else
			printf("%s", buff);
		bytes = read(fd, buff, buff_size);
	}
	return (NULL);
}

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("README.md", O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		free(line);	
	}
	return (close(fd));
	// while ((line = get_next_line(fd)))
	// 	printf("%s", line);
}
