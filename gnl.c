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


#define BUFFER_SIZE 1024
#define CACHE_SIZE 100000

char *get_next_line(int fd)
{
    static char cache[CACHE_SIZE];
    static int start = 0, end = 0;
    char *line;
    int  i,j,bytes;
    // Leggi i dati nel buffer cache
    while ((bytes = read(fd, cache + end, BUFFER_SIZE)) > 0)
    {
        end += bytes;
        if (end >= CACHE_SIZE) // Evita overflow
            break;
    }
    if (bytes < 0 || (start == end && !bytes))
        return NULL;
    // Trova la fine della riga (newline o fine del buffer)
    for (i = start; i < end && cache[i] != '\n'; i++);
    // Alloca memoria per la riga (includendo newline e terminatore nullo)
    line = malloc(i - start + 2); // +2 per newline e terminatore nullo
    if (!line)
        return NULL;
    // Copia la riga nel buffer allocato
    for ( j = 0; start < i; j++)
        line[j] = cache[start++];    
    // Aggiungi il newline (se presente) e il terminatore nullo
    if (i < end && cache[i] == '\n')
        line[j++] = cache[start++];
    line[j] = '\0';
    return line;
}

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define CACHE_SIZE 100000
#define LINE_SIZE 1024 // Dimensione massima della riga

char *get_next_line(int fd)
{
    static char cache[CACHE_SIZE];
    static int start = 0, end = 0;
    static char line[LINE_SIZE]; // Buffer statico per la riga
    int i, j, bytes;

    // Leggi i dati nel buffer cache
    while ((bytes = read(fd, cache + end, BUFFER_SIZE)) > 0)
    {
        end += bytes;
        if (end >= CACHE_SIZE) // Evita overflow
            break;
    }

    if (bytes < 0 || (start == end && !bytes))
        return NULL;

    // Trova la fine della riga (newline o fine del buffer)
    for (i = start; i < end && cache[i] != '\n'; i++);

    // Copia la riga nel buffer statico
    for (j = 0; start < i && j < LINE_SIZE - 1; j++)
        line[j] = cache[start++];

    // Aggiungi il newline (se presente) e il terminatore nullo
    if (i < end && cache[i] == '\n' && j < LINE_SIZE - 1)
        line[j++] = cache[start++];
    line[j] = '\0';

    return line;
}
char *get_next_line(int fd)
{
    static char cache[100000];
    static char result[10000];
    static int start = 0, end = 0;
    int i, j, bytes;
    
    // Leggi solo se necessario
    if (start >= end) {
        start = 0;
        end = 0;
        if ((bytes = read(fd, cache, 10000)) <= 0)
            return NULL;
        end = bytes;
    }
    
    // Trova la fine della riga
    for (i = start; i < end && cache[i] != '\n'; i++);
    
    // Copia la riga nel buffer di risultato statico
    for (j = 0; start < i; j++)
        result[j] = cache[start++];
    
    // Gestisci il newline se presente
    if (i < end && cache[i] == '\n') {
        result[j++] = '\n';
        start++;
    }
    
    // Aggiungi il terminatore di stringa
    result[j] = '\0';
    
    // Se abbiamo raggiunto la fine del buffer ma non c'è un newline,
    // potremmo dover leggere ancora al prossimo chiamata
    return result[0] ? result : NULL;
}

char *get_next_line(int fd)
{
    static char cache[100000], result[10000];
    static int start = 0, end = 0;
    int i, j, bytes;
    if (start >= end) 
    {
        start = 0; end = 0;
        if ((bytes = read(fd, cache, 10000)) <= 0) return NULL;
        end = bytes;
    }
    for (i = start; i < end && cache[i] != '\n'; i++);
    for (j = 0; start < i; j++) result[j] = cache[start++];
    if (i < end && cache[i] == '\n') { result[j++] = '\n'; start++; }
    result[j] = '\0';
    return result[0] ? result : NULL;
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

