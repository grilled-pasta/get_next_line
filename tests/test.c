/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alkonsta@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 00:10:49 by alla              #+#    #+#             */
/*   Updated: 2026/10/10 00:11:01 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include <stddef.h>

void	test_one_line(void);
void	test_multiple_lines(void);
void	test_empty(void);
void	test_no_newline(void);
void	test_consecutive_lines(void);
void	test_long_line(void);
void	test_eof_after_final_line(void);
void	test_crlf(void);
void	test_spaces_and_tabs(void);
void	test_unicode_utf8(void);

int	main(void)
{
	printf("TESTING:\n");
	test_one_line();
	test_multiple_lines();
	// test_empty();
	// test_no_newline();
	// test_consecutive_lines();
	// test_long_line();
	// test_eof_after_final_line();
	// test_crlf();
	// test_spaces_and_tabs();
	// test_unicode_utf8();
	return (0);
}

/*
 * 1) "Hello\n"
 * 2) NULL
 */
void	test_one_line(void)
{
	// files/one_line.txt
	int		fd;
	char	*line;

	fd = open("tests/files/one_line.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);	
	}
	close(fd);
}

/*
 * 1) "Hello\n"
 * 2) "World\n"
 * 3) "CODAM\n"
 * 4) NULL
 */
void	test_multiple_lines(void)
{
	// files/multiple_lines.txt	
	int		fd;
	char	*line;

	fd = open("tests/files/multiple_lines.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR CREATING FD");
		return ;
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);	
	}
	close(fd);
}

/*
 * 1) NULL
 */
void	test_empty(void)
{
	// files/empty.txt
}

/*
 * 1) "Hello"
 * 2) NULL
 */
void	test_no_newline(void)
{
	// files/no_newline.txt
}

/*
 * 1) "A\n"
 * 2) "\n"
 * 3) "B\n"
 * 4) NULL
 */
void	test_consecutive_lines(void)
{
	// files/consecutive_lines.txt
}

/*
 * 1) 5000 x "A\n"
 * 2) NULL
 *
 * ! BUFFER SIZE 1, 7, 42
 */
void	test_long_line(void)
{
	// files/long_line.txt
}

/*
 * 1) "A\n"
 * 2) "B"
 * 3) NULL
 */
void	test_eof_after_final_line(void)
{
	// files/eof_after_final_line.txt
}

/*
 * 1) "First line\r\n"
 * 2) "Second line\r\n"
 * 3) NULL 
 */
void	test_crlf(void)
{
	// files/crlf.txt
}

/*
 * 1) " leading space\n"
 * 2) "\tleading tab\n"
 * 3) "trailing spaces    \n"
 * 4) NULL
 */
void	test_spaces_and_tabs(void)
{
	// files/spaces_and_tabs.txt
}

/*
 * 1) "café\n"
 * 2) "naïve\n"
 * 3) "日本語\n"
 * 4) NULL
 */
void	test_unicode_utf8(void)
{
	// files/unicode_utf8.txt
}
