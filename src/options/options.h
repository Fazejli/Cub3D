/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:37:42 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:38:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include <stdint.h>

typedef struct s_options {
	const char		**texture_names;
	uint32_t		texture_count;
	uint32_t		width;
	uint32_t		height;
	int16_t			thread_count;
	char			reserved[2];
}	t_options;

int	options_init(t_options *opt, int argc, char **argv);

#endif
