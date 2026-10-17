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

#include "get_next_line_bonus.h"

/*
 * This function returns a string that contains at least one new line, or the 
 * contents before reaching EOF. It handles processing the remainder of a
 * previous file read. 
 * Returns NULL if memory allocation fails, or the was an error while reading
 * from the file.
 */
static char	*read_next_line(int fd, char *buff)
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

/*
 * This function handles reading a file line by line. It returns a string
 * containing the next new line in the file. Repeated calls return the next new
 * line encountered in the file. It handles reading from multiple files.
 * Returns NULL if the file descriptor is invalid, if memory allocation fails,
 * or if EOF is reached and there is nothing more to read.
 */
char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char		*new_line;
	int			i;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
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

// #include <stdio.h>
// #include <fcntl.h>
//
// int	main(void)
// {
// 	int		fd, fd2;
// 	char	*line;
//
// 	fd = open("README.md", O_RDONLY);
// 	fd2 = open("tests/files/multiple_lines.txt", O_RDONLY);
//
// 	line = get_next_line(fd);
// 	printf("~~%s", line);
// 	free(line);
//
// 	line = get_next_line(fd2);
// 	printf("~~%s", line);
// 	free(line);	
//
// 	line = get_next_line(fd);
// 	printf("~~%s", line);
// 	free(line);
//
// 	line = get_next_line(fd2);
// 	printf("~~%s", line);
// 	free(line);	
//
// 	return (close(fd) && close(fd2));
// }
