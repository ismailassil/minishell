/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:27:22 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 12:30:35 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_exported_variable(t_env *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		printf("declare -x ");
		i = 0;
		while (envp->value[i] != '\0')
		{
			if (envp->value[i] == '=' && envp->value[i] != '\0')
				printf("=\"");
			else
				printf("%c", envp->value[i]);
			i++;
		}
		printf("\"\n");
		envp = envp->next;
	}
}
