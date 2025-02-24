char *get_line(char *str, int start, int end)
{
    char *res = malloc((end - start  + 1) * sizeof(char));
    if (!res)
        return (0);
    for (int i = 0; i < end - start; ++i)
        res[i] = str[start + i];
    res[end - start] = '\0';
    return (res);
}

char *get_next_line(int fd)
{
    char buff[BUFFER_SIZE];
    static char cache[100000];
    static int start = 0;
    static int end = 0;
    while(1)
    {
        int bytes = read(fd, buff, BUFFER_SIZE);
        if (bytes > 0)
        {
            for (int i = 0; i < bytes; ++i)
                cache[end++] = buff[i];
            continue;
        }
        else if (bytes < 0)
            return (0);
        else
            break;
    }
    if (start == end)
        return (0);
    for (int i = start; i < end; ++i)
    {
        if (cache[i] == '\n')
        {
            char *line = get_line(cache, start, i + 1);
            start = i + 1;
            return (line);
        }
    }

    char *line = get_line(cache, start, end);
    start = end;
    return (line);
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

