/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:37:37 by iassil            #+#    #+#             */
/*   Updated: 2024/04/27 23:18:32 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env *env)
{
	t_env	*head;
	int		flag;

	head = env;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			printf("%s\n", head->value + 4);
			flag = 1;
			break ;
		}
		head = head->next;
	}
	if (flag == 0)
		printf("%s\n", getcwd(0, 0));
	ft_add_path_executed_cmd("pwd", env);
}
