/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:24 by iassil            #+#    #+#             */
/*   Updated: 2024/03/24 21:51:41 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *argument)
{
	int	i;
	int	len;

	i = 0;
	if (argument == NULL)
		return ;
	len = ft_strlen(argument);
	while (argument[i] != '\0')
		(write(1, &argument[i], 1), i++);
}

// int	main(int ac, char **av)
// {
// 	ft_echo(atoi(av[1]), "\"\'hello world\'\"");
// 	return (0);
// }
