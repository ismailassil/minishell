/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:27:22 by iassil            #+#    #+#             */
/*   Updated: 2024/03/21 15:46:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate_for_env(t_env **head, t_env *envp)
{
	*head = malloc(sizeof(t_env));
	ft_check_allocation(head);
	*head = NULL;
	while (envp)
	{
		ft_push_value(envp->value, head);
		envp = envp->next;
	}
	ft_sort_list(head);
}

void	ft_print_exported_variable(t_env *envp)
{
	int		i;
	int		flag;
	t_env	*head;

	(1) && (flag = 0, i = 0);
	ft_allocate_for_env(&head, envp);
	while (head)
	{
		printf("declare -x ");
		i = 0;
		while (head->value[i] != '\0')
		{
			if (head->value[i] == '=' && head->value[i] != '\0')
				(printf("=\""), flag = 1);
			else
				printf("%c", head->value[i]);
			i++;
		}
		if (flag == 1)
			(1) && (printf("\""), flag = 0);
		printf("\n");
		head = head->next;
	}
	ft_free_env(&head);
}

char	*ft_get_cwd(t_env **envp)
{
	char	*buffer;
	t_env	*head;

	head = *envp;
	buffer = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, "PWD=", 4) == 0)
		{
			buffer = ft_strdup(head->value + 4);
			break ;
		}
		head = head->next;
	}
	return (buffer);
}

char	*ft_filter_arg(char *arg)
{
	char	*value;
	t_in	inf;

	(1) && (inf.i = 0, inf.count = 0);
	while (arg[inf.i] != '\0')
	{
		if (arg[inf.i] == '\"' || arg[inf.i] == '\"')
			inf.count++;
		inf.i++;
	}
	value = (char *)malloc((inf.i - inf.count + 1) * sizeof(char));
	if (!value)
		return (NULL);
	(1) && (inf.i = 0, inf.j = 0);
	while (arg[inf.i] != '\0')
	{
		if (arg[inf.i] == '\"' || arg[inf.i] == '\'')
			inf.i++;
		else
			(1) && (value[inf.j] = arg[inf.i], inf.i++, inf.j++);
	}
	value[inf.j] = '\0';
	return (value);
}

bool	ft_check_syntax_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isalpha(arg[0]) == 0 || arg[0] == '-')
	{
		(ft_error("msh: export: "), ft_error(arg));
		ft_error(": not a valid identifier\n");
		return (true);
	}
	while (arg && arg[i] != '\0' && arg[i] != '=')
	{
		if (arg[i] == '-' || (arg[i] == '+' && arg[i + 1] != '\0'
				&& arg[i + 1] != '='))
		{
			(ft_error("msh: export: "), ft_error(arg));
			ft_error(": not a valid identifier\n");
			return (true);
		}
		i++;
	}
	return (false);
}
