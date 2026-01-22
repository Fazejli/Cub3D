#ifndef GNL_H
# define GNL_H

#ifndef BS
# define BS 42
#endif

#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char *gnl(int fd);

#endif