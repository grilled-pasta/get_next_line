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
	while (*s && *s != '\n')
		s++;
	return (*s == '\n');
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
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

char	*get_next_line(int fd)
{
	static char	*remainder;
	int			bytes;
	int			buff_size;
	char		*buff;
	int			i;
	int			j;
	char		*new_line;

	buff_size = 10;
	buff = (char *) malloc(sizeof(char) * buff_size + 1);
	while (remainder || (bytes = read(fd, buff, buff_size)) > 0)
	{	
		if (remainder)
		{
			ft_memcpy(buff, remainder, ft_strlen(remainder) + 1);
			free(remainder);
			remainder = NULL;
		}
		if (contains_new_line(buff))
		{
			i = 0;
			while (buff[i])
			{
				if (buff[i] == '\n' && buff[i + 1])
				{
					remainder = (char *) malloc(sizeof(char) * ft_strlen(buff + i + 1) + 1);
					ft_memcpy(remainder, buff + i + 1, ft_strlen(buff + i + 1) + 1);
					buff[i + 1] = '\0';
					break ;
				}
				// else
				// {
				// 	free(remainder);
				// 	remainder = NULL;
				// }
				i++;
			}
			printf("%s~~~", buff);
			return (buff);
		}
		else
		{
			// free(remainder);
			// remainder = NULL;
			printf("___%s___", buff);
		}
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
