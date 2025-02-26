#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    static char c[100000];
    static int i, r, n;
    char *s;
    int j = 0;
    
    if (i >= r)
        i = 0, r = 0;
    while (!n && (r == 0 || c[i + j - 1] != '\n'))
        if ((n = j >= r - i) && (r += read(fd, c + r, BUFFER_SIZE)) <= i)
            return (i < r) ? get_next_line(fd) : NULL;
        else
            j++;
    s = malloc(j + 1);
    if (!s)
        return NULL;
    j = 0;
    while (i < r && c[i] != '\n')
        s[j++] = c[i++];
    if (i < r && c[i] == '\n')
        s[j++] = c[i++];
    s[j] = 0;
    n = 0;
    return s;
}

# include <stdio.h>
int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}

