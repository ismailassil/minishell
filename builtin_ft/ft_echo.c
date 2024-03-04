/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:24 by iassil            #+#    #+#             */
/*   Updated: 2024/03/04 14:56:20 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(int n, t_env *envp, char *argument)
{
	int	i;
	int	len;

	i = 0;
	if (argument == NULL)
		return ;
	len = ft_strlen(argument);
	while (argument[i] != '\0')
	{
		if (i == 0 && (argument[i] == '\"' || argument[i] == '\'')
			&& argument[i + 1] != '\0')
			i++;
		else if (i == len - 1 && (argument[i] == '\"' || argument[i] == '\''))
			i++;
		else
			(write(1, &argument[i], 1), i++);
	}
	if (n == 0)
		write(1, "\n", 1);
}

// int	main(int ac, char **av)
// {
// 	ft_echo(atoi(av[1]), av[2]);
// 	return (0);
// }
