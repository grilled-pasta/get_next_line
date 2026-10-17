_This project has been created as part of the 42 curriculum by alkonsta_
# get_next_line
## Description
A function that returns a line read from a file descriptor. Repeated calls return the next string containing a new line or the remaining contents of the file before reaching `EOF`.

Returns `NULL` if:
- the file descriptor or `BUFFER_SIZE` are invalid.
- memory allocation fails.
- `EOF` is reached.

The size of every `read()` call is set at compile time with `-D BUFFER_SIZE=n` (it defaults to `1`).
The **bonus** part handles multiple file descriptors at the same time, where the remainder is saved for each one.
### Prototype
```c 
char    *get_next_line(int fd);
```
## Instructions
### Compile
#### Mandatory:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=48 \
    get_next_line.c get_next_line_utils.c
```
#### Bonus:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=48 \
    get_next_line_bonus.c get_next_line_bonus_utils.c
```
#### Usage
```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("README.md", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);	
	}
    close(fd);
	return (0);
}
```
## Resources
- [C Programming](https://nmu.edu/Webb/ArchivedHTML/MathComputerScience/c_programming/c_075.htm)
- [4.5.5 Storage class qualifiers](https://cs.yale.edu/homes/aspnes/classes/223/notes.html)
- [Huge array in local vs global variable](https://stackoverflow.com/a/5352028)
## Algorithm
### Idea
Data is read from the file in chunks of `BUFFER_SIZE` bytes, but a chunk almost never ends exactly at the end of a line. Whatever was read after the `\n` must be saved, because the next call has to start there. The solution is a **static buffer** (`static char buff[BUFFER_SIZE + 1]`) that survives between calls and stores this leftover. The buffer is always NULL-terminated and an empty string means "no leftover".
### Step by step
`get_next_line(fd)` works in two stages.
1. `read_next_line`: build a string that holds at least one full line
    1. If the static buffer holds leftover data, copy it into a new string and clear the buffer.
    2. While the string does not contain `\n`:
        - `read(fd, buff, BUFFER_SIZE)` and NULL-terminate what was read.
        - Append the buffer to the string (`ft_dupcat` allocates the new string and frees the old one), then clear the buffer.
    3. Stop on one of these conditions:
        - A `\n` was found: return the string.
        - `read` returned `0` (EOF): return what has been collected so far, which is `NULL` if nothing was read.
        - `read` returned `-1` or `malloc` failed: free everything, clear the buffer and return `NULL`.
2. **Split the string at the first `\n`**
    1. Find the first `\n`.
    2. If characters follow it, copy them into the static buffer (they become the lefover for the next call), cut the string right after the `\n` ans shrink it with `ft_dupcat(line, NULL)`.
    3. Return the line.
## Use of AI
> Claude was used to review the finished code and to help structure and draft this README. The implementation and choice of algorithm are my own work.