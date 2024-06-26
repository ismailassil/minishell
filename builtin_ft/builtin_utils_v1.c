/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_v1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:27:22 by iassil            #+#    #+#             */
/*   Updated: 2024/04/28 15:03:07 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_null_export(t_env *head)
{
	while (head)
	{
		if (head->value[0] == '_' && head->value[1] == '=')
			head = head->next;
		else
		{
			ft_putstr("declare -x ", 1);
			ft_print_rest(head->value);
			head = head->next;
		}
	}
}

void	ft_print_exported_variable(t_env *envp)
{
	t_env	*head;

	head = NULL;
	while (envp)
	{
		ft_push_value(envp->value, &head);
		envp = envp->next;
	}
	ft_sort_list(&head);
	ft_print_null_export(head);
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
	ft_check_allocation(value);
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
	if (arg && ft_isalpha(arg[0]) == 0 && arg[0] != '_')
	{
		(ft_error("msh: export: \'"), ft_error(arg));
		ft_error("\': not a valid identifier\n");
		return (true);
	}
	while (arg && arg[i] != '\0' && arg[i] != '=')
	{
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_' && arg[i] != '+')
			|| (arg[i] == '+' && arg[i + 1] != '\0' && arg[i + 1] != '=')
			|| (arg[i] == '+' && arg[i + 1] == '\0'))
		{
			(ft_error("msh: export: \'"), ft_error(arg));
			ft_error("\': not a valid identifier\n");
			return (true);
		}
		i++;
	}
	return (false);
}
