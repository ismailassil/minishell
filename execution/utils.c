/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:43:43 by iassil            #+#    #+#             */
/*   Updated: 2024/03/17 17:23:39 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_allocation(void *str)
{
	if (str == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
}

void	ft_syscall(int return_, char *str)
{
	if (return_ == -1)
		(perror(str), exit(FAIL));
}

void	ft_f(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
