/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:20 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:40:52 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	if (lst->content && !lst->next)
		return (1);
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
