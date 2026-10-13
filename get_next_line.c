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
	while (*s && *s != '\n' && *s != EOF)
		s++;
	return (*s == '\n' || *s == EOF);
}

int		ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_dupcat(char *s1, char *s2)
{
	char	*res;
	char	*str;

	res = (char *) malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	str = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buff[BUFFER_SIZE + 1];
	int			i;
	int			bytes;
	char		*new_line;
	char		*temp;

	temp = NULL;
	new_line = ft_dupcat("", "");
	if (stash)
	{
		new_line = ft_dupcat(new_line, stash);
		free(stash);
		stash = NULL;
	}
	if (contains_new_line(new_line))
	{
		i = 0;
		while (new_line[i])
		{
			if (new_line[i] == '\n' || new_line[i] == EOF)
			{
				if (new_line[i + 1])
				{
					stash = ft_dupcat("", new_line + i + 1);
					new_line[i + 1] = '\0';
				}
				break ;
			}
			i++;
		}
		return (new_line);
	}
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (contains_new_line(buff))
		{
			i = 0;
			while (buff[i])
			{
				if (buff[i] == '\n' || buff[i] == EOF)
				{
					if (buff[i + 1])
					{
						stash = ft_dupcat("", buff + i + 1);
						buff[i + 1] = '\0';
					}
					break ;
				}
				i++;
			}
			temp = new_line;
			new_line = ft_dupcat(new_line, buff);
			free(temp);
			return (new_line);
		}
		else
		{
			temp = new_line;
			new_line = ft_dupcat(new_line, buff);
			free(temp);
		}
	}
	return (NULL);
}

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
// 		printf("%s", line);
// 		free(line);	
// 	}
// 	return (close(fd));
// }
