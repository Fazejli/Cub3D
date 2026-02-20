/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:44:43 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 14:07:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "gfx/gfx.h"
#include "renderer.h"
#include "options/options.h"

static int	renderer_init_framebuffers(t_renderer *r, const t_options *opt)
{
	int	i;

	i = 0;
	while (i < FRAMEBUFFER_COUNT)
	{
		// todo cleanup
		if (gfx_image_create(r->gfx, &r->framebuffers[i], opt->width,
				opt->height))
			return (1);
		i++;
	}
	return (0);
}

int	renderer_init(t_renderer *r, const t_options *opt)
{
	if (renderer_init_framebuffers(r, opt))
		return (1);
	return (0);
}
