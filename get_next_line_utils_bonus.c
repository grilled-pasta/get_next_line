/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:04:53 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/16 20:07:13 by alkonsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Returns 1 if the string _s_ contains at least one new line character.
 * Returns 0 if the string _s_ is NULL or doesn't contain a new line.
 */
int	contains_new_line(char *s)
{
	while (s && *s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

/*
 * Returns the length of the string
 * Returns 0 if the string is NULL or empty. 
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/*
 * Given two strings _s1_ and _s2_, this function generates a new string that 
 * is the result of the concatenation of _s1_ and _s2_. It also calls _free()_
 * on first argument _s1_. The result is always NULL-terminated. Passing NULL
 * values is valid and it is handled by the function.
 * Returns NULL if the allocation fails.
 */
char	*ft_dupcat(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (free(s1), res);
}

/*
 * This function accepts a pointer to a memory area and its size. It sets its 
 * memory for the first _n_ bytes to zero. 
 * The argument must be a valid, non-NULL pointer.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = 0;
		i++;
	}
}

/*
 * This function accepts two strings and the number of bytes to process. It 
 * copies the first _n_ bytes from _src_ into _dest_.
 * The arguments must be a valid, non-NULL pointer.
 */
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
