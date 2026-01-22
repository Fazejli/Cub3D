#include "../../inc/cub3d.h"
#include "../../inc/gnl.h"

char *gnl(int fd)
{
    char line[100];
    static char buffer[BS];
    static int temp = 0;
    static int buffer_pos = 0;
    int         i = 0;

    while (1)
    {
        if (buffer_pos >= temp)
        {
            temp = read(fd, buffer, BS);
            buffer_pos = 0;
            if (temp <= 0)
                break ;
        }
        line[i++] = buffer[buffer_pos++];
        if (line [i - 1] == '\n')
            break ;
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}