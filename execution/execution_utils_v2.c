/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_v2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:49:47 by iassil            #+#    #+#             */
/*   Updated: 2024/04/06 03:16:43 by iassil           ###   ########.fr       */
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
			head->value = ft_join_("_=", str);
			ft_check_allocation(head->value);
			return ;
		}
		head = head->next;
	}
	if (flag == 0)
	{
		cmd = ft_join_("_=", str);
		ft_check_allocation(cmd);
		ft_push_value(cmd, &env);
		free(cmd);
	}
}

void	ft_add_cmd_or_arg_to_env(int nr_cont, t_cont *cont, t_struct *strp)
{
	int	i;

	i = 0;
	if (nr_cont == 1 && cont->cmd != NULL)
	{
		if (cont->arg == NULL || cont->arg[0] == 0)
			ft_add_path_executed_cmd(cont->cmd, strp->env);
		else
		{
			while (cont->arg && cont->arg[i])
				i++;
			ft_add_path_executed_cmd(cont->arg[i - 1], strp->env);
		}
	}
	else if (nr_cont > 1)
		ft_delete_node(&strp->env);
}

void	ft_return_path(char **path, char *cmd, t_struct *strp, t_cont *cont)
{
	ft_f(path);
	ft_error("msh: ");
	ft_error(cmd);
	ft_error(": command not found\n");
	ft_exitf(&strp, &cont);
	free(strp);
}
