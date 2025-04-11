#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

char *ft_strdup(char *s)
{
    int i = 0;
    char *new_s;
    int len = 0;

    if (!s)
        return (NULL);
    while (s[len])
        len++;
    new_s = malloc(len + 1);
    while (s[i])
    {
        new_s[i] = s[i];
        i++;
    }
    new_s[i] = '\0';
    return (new_s);
}

char *get_next_line(int fd)
{
    static char buffer[700000];
    static char line[70000];
    static int buffer_read;
    static int buffer_pos;
    int i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    i = 0;
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        line[i++] = buffer[buffer_pos++];
        if (buffer[buffer_pos - 1] == '\n' || i >= (int)sizeof(line) - 1)
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return NULL;
    return (ft_strdup(line));
}

// int main()
// {
//     int fd = open("test.txt", O_RDONLY);
//     char *line;

//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s", line);
//         free(line); 
//     }
//     close(fd);
//     return 0;
// }