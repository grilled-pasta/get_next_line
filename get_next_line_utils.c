/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alkonsta@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 00:27:47 by alla              #+#    #+#             */
/*   Updated: 2026/10/10 00:27:48 by alla             ###   ########.fr       */
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


