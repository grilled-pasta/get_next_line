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

int		contains_new_line(char *s)
{
	while (s && *s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int		ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_dupcat(char *s1, char *s2)
{
	char	*res;
	char	*str;

	res = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	str = res;
	while (s1 && *s1)
		*res++ = *s1++;
	while (s2 && *s2)
		*res++ = *s2++;
	*res = '\0';
	return (str);
}

void	ft_strzero(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		((unsigned char *) s)[i] = '\0';
		i++;
	}
}

void	*ft_memcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dest);
}

char	*read_next_line(int fd, char (*buff)[BUFFER_SIZE + 1])
{
	int			bytes;
	char		*new_line;
	char		*temp;

	new_line = NULL;
	while (!contains_new_line(*buff))
	{		
		temp = new_line;
		new_line = ft_dupcat(new_line, *buff);
		if (!new_line)
			return (free(temp), ft_strzero(*buff), NULL);
		free(temp);
		bytes = read(fd, *buff, BUFFER_SIZE);
		if (bytes == 0)
			return (ft_strzero(*buff), new_line);
		if (bytes == -1)
			return (ft_strzero(*buff), free(new_line), NULL);
		*buff[bytes] = '\0';
		// temp = new_line;
		// new_line = ft_dupcat(new_line, *buff);
		// if (!new_line)
		// 	return (free(temp), ft_strzero(*buff), NULL);
		// free(temp);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*new_line;
	int			i;

	new_line = read_next_line(fd, &buff);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	i++;
	// printf("BUFF: %s\n", buff);
	ft_strzero(buff);
	if (new_line + i + 1)
		ft_memcpy(buff, new_line + i + 1, ft_strlen(new_line + i + 1) + 1);
	new_line[i] = '\0';
	return (new_line);
}

int		main(void)
{
	int		fd;
	char	*line;

	// fd = open("multinewlines.txt", O_RDONLY);
	fd = open("README.md", O_RDONLY);
	if (fd == -1)
		return (-1);
	// while ((line = get_next_line(fd)))
	// {
	// 	printf("~~%s\n", line);
	// 	free(line);	
	// }
	line = get_next_line(fd);
	printf("~~%s\n", line);	
	line = get_next_line(fd);
	printf("~~%s\n", line);
	free(line);
	return (close(fd));
}
