/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:45:50 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 03:18:33 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "mapping_internal.h"

static bool	is_valid_name(const char *path) //here or before ?
{
	const char	*find;

	if (!path || strlen(path) < 5)
		return (false);
	find = memmem(path, strlen(path) + 1, ".cub\0", 5);
	if (!find || find[-1] == '/')
		return (false);
	return (true);
}

void	unmap_file(t_file *file)
{
	if (!file || !file->data || file->size <= 0)
		return ;
	munmap((void *)file->data, file->size);
	*file = (t_file){0};
}

t_file	map_file(const char *path)
{
	struct stat	st;
	t_file		file;
	int			fd;

	file.error = ERR_NONE;
	if (!is_valid_name(path))
		return ((t_file){.error = ERR_INVALID_NAME});
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((t_file){.error = ERR_PERROR});
	fstat(fd, &st);
	if (st.st_size <= 0)
		return ((t_file){.error = ERR_UNKNOWN}); //to be defined in error.h
	file.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file.data == MAP_FAILED)
		return ((t_file){.error = ERR_PERROR});
	close(fd);
	file.path = path;
	file.size = st.st_size;
	file.error = ERR_NONE;
	return (file);
}
