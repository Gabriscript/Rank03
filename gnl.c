#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int index = 0, bytes_read = 0;
    char *line;
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0) 
    return NULL;
    line = malloc(BUFFER_SIZE + 1);
    if (!line)
        return NULL;
    while (1)
    {
        if (index >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            index = 0;
            if (bytes_read <= 0)
            {
                free(line);
                return NULL;
            }
        }
        line[i++] = buffer[index++];
        if (buffer[index - 1] == '\n' || index >= bytes_read)
            break;
    }
    line[i] = '\0';
    return line;
}

