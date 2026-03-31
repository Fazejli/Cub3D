/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:56:47 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 19:46:04 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

#ifdef DEBUG

# include <stddef.h>
# include <stdio.h>

void	debug_print_options(t_options *options)
{
	printf("\t\t- OPTIONS -\n\n");
	printf("- File path: %s\n", options->file_path);
	printf("- Width: %u\n", options->width);
	printf("- Height: %u\n", options->height);
	printf("- Thread count: %d\n", options->thread_count);
	printf("- FPS: %d\n\n", options->fps);
}

#else

void	debug_print_options(t_options *options)
{
	(void)options;
}

#endif
