/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:06:34 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:40:46 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s;
	t_list	*ptr;

	if (!lst)
		return (0);
	s = NULL;
	while (lst)
	{
		ptr = ft_lstnew(f(lst->content));
		if (!ptr)
		{
			ft_lstclear(&s, del);
			return (0);
		}
		ft_lstadd_back(&s, ptr);
		lst = lst->next;
	}
	return (s);
}
