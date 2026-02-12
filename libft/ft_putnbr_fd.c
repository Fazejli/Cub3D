/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:44:46 by fadzejli          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:12 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lnb;

	lnb = n;
	if (lnb < 0)
	{
		lnb = -lnb;
		ft_putchar_fd('-', fd);
	}
	if (lnb <= 9)
		ft_putchar_fd(lnb + '0', fd);
	else
	{
		ft_putnbr_fd(lnb / 10, fd);
		ft_putnbr_fd(lnb % 10, fd);
	}
}
/*
int	main()
{
	ft_putnbr_fd(2147483648, 1);
	return (0);
}*/