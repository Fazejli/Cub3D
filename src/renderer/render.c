/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:14:46 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 14:20:29 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <stdio.h>
#include <unistd.h>

void	renderer_render(t_renderer *r)
{
	printf("Rendering...\n");
	usleep(100000);
	(void)r;
}
