/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:07:55 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/16 20:09:31 by alkonsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		contains_new_line(char *s);
int		ft_strlen(const char *s);
char	*ft_dupcat(char *s1, char *s2);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(char *dest, char *src, size_t n);

#endif 
