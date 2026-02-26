/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:02:33 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 11:07:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// todo temp
__attribute__((unused))
static bool	is_valid_name(const char *path)
{
	const char	*find;

	if (!path || strlen(path) < 5)
		return (false);
	find = memmem(path, strlen(path) + 1, ".cub\0", 5);
	if (!find || find[-1] == '/')
		return (false);
	return (true);
}

t_file	map_file(const char *path)
{
	struct stat	st;
	t_file		file;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "Error: could not open file %s\n", path);
		return ((t_file){0});
	}
	fstat(fd, &st);
	if (st.st_size <= 0)
	{
		dprintf(2, "Error: file %s is not seekable\n", path);
		return ((t_file){0});
	}
	file.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file.data == MAP_FAILED)
	{
		dprintf(2, "Error: %m\n");
		return ((t_file){0});
	}
	close(fd);
	file.path = path;
	file.size = st.st_size;
	return (file);
}

void	unmap_file(t_file *file)
{
	munmap((void *)file->data, file->size);
}
