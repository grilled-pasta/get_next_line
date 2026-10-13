/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkonsta <alkonsta@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 20:29:29 by alkonsta          #+#    #+#             */
/*   Updated: 2026/10/09 21:48:21 by alkonsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

// typedef	struct	fd_str
// {
// 	int		fd;
// 	char	*str;
// }			t_fd_str;

char	*get_next_line(int fd);

#endif 
