/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:49:47 by iassil            #+#    #+#             */
/*   Updated: 2024/03/29 02:41:17 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_node(t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "_=", 2) == 0)
		{
			free(head->value);
			head->value = NULL;
			head->value = ft_strdup("_=");
			return ;
		}
		head = head->next;
	}
}

void	ft_add_path_executed_cmd(char *str, t_env *env)
{
	t_env	*head;
	char	*cmd;
	int		flag;
	int		i;

	(1) && (head = env, i = 0, flag = 0);
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "_=", 2) == 0)
		{
			(free(head->value), head->value = NULL);
			head->value = ft_strjoin_("_=", str);
			ft_check_allocation(head->value);
			return ;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cmd = ft_strjoin_("_=", str);
		ft_check_allocation(cmd);
		ft_push_value(cmd, &env);
		free(cmd);
	}
}
