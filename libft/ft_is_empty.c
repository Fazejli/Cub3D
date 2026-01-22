#include "libft.h"

int	ft_is_empty(char *line)
{
	int	i;

	if (!line)
		return (1);

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
