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
	if (!s)
		return (0);
	while (*s && *s != '\n')
		s++;
	return (*s == '\n');
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	int			i;
	int			bytes;
	char		*new_line;
	char		*temp;

	if (fd < 0)
		return (NULL);
	temp = NULL;
	new_line = NULL;
	buff = NULL;
	if (stash)
	{
		new_line = ft_dupcat("", stash);
		if (!new_line)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		free(stash);
		stash = NULL;
	}
	while(!contains_new_line(new_line))
	{
		buff = (char *) malloc(BUFFER_SIZE + 1);
		if (!buff)
		{
			free(new_line);
			return (NULL);
		}
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == 0)
		{
			free(buff);
			break ;
		}
		if (bytes < 0)
		{
			free(new_line);
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		temp = new_line;
		new_line = ft_dupcat(new_line, buff);
		if (!new_line)
		{
			free(temp);
			free(buff);
			return (NULL);
		}
		free(temp);
		free(buff);
	}
	i = 0;
	while (new_line && new_line[i])
	{
		if (new_line[i] == '\n')
		{
			if (new_line[i + 1])
			{
				if (stash)
				{
					free(stash);
					stash = NULL;
				}
				stash = ft_dupcat("", new_line + i + 1);
				if (!stash)
				{
					free(new_line);
					free(buff);
					return (NULL);
				}
				new_line[i + 1] = '\0';
			}
			// new_line[i] = '_';
			break ;
		}
		i++;
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
// 		printf("%s", line);
// 		free(line);	
// 	}
// 	return (close(fd));
// }
