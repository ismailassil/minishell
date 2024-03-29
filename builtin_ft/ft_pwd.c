/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:37:37 by iassil            #+#    #+#             */
/*   Updated: 2024/03/29 02:27:59 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env *env)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			printf("%s\n", head->value + 4);
			break ;
		}
		head = head->next;
	}
	ft_add_path_executed_cmd("pwd", env);
}
