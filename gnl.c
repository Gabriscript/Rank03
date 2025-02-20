
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> //solo per il test in main

char	*get_next_line(int fd)
{
	static char buffer[9999999];
	char		*ret = buffer;
	int			i = 0;

	if (fd < 0)
		return (NULL);
	while (read(fd, &buffer[i], 1) > 0)
	{
		if (buffer[i++] == '\n')
			break;
	}
	if (i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (ret);
}

// Main solo per test
int	main(int argc, char **argv)
{
	int		fd = 0;
	char	*line;

	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("line |%s", line);
		line = get_next_line(fd);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

