/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:17:46 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:20:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	a;

	if (fd < 0)
		return ;
	a = (long int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		a = -a;
	}
	if (a > 9)
	{
		ft_putnbr_fd(a / 10, fd);
		ft_putchar_fd((a % 10) + '0', fd);
	}
	if (a >= 0 && a <= 9)
		ft_putchar_fd(a + '0', fd);
}
