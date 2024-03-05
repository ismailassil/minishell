/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:27:22 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 16:30:38 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_if_not_found(t_env **envp, int flag, char *arg, char *string)
{
	char	*tmp;

	if (flag == 0)
	{
		tmp = ft_strjoin(string, arg);
		if (!tmp)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		if (ft_push_value(tmp, envp) == 0)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		(1) && (free(tmp), tmp = NULL);
	}
}

void	ft_add_current_pwd(t_env **envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = *envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			(1) && (free(head->value), head->value = NULL);
			tmp = ft_strjoin("PWD=", argument);
			if (!tmp)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "PWD=");
}

void	ft_add_old_pwd(t_env **envp, char *argument)
{
	t_env	*head;
	int		flag;
	char	*tmp;

	head = *envp;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "OLDPWD=", 4) == 0)
		{
			(1) && (free(head->value), head->value = NULL);
			tmp = ft_strjoin("OLDPWD=", argument);
			if (!tmp)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			head->value = tmp;
			flag = 1;
			break ;
		}
		head = head->next;
	}
	ft_add_if_not_found(envp, flag, argument, "OLDPWD=");
}

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
