/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/21 17:42:59 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_check_if_exists(char *arg, t_env *envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = envp;
	while (arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
		i++;
	while (head != NULL)
	{
		if (ft_strncmp(arg, head->value, i) == 0)
			return (true);
		head = head->next;
	}
	return (false);
}

static char	*ft_append_value(char *arg, char *old_arg, int flag)
{
	t_append_export	f;

	(1) && (f.value = ft_filter_arg(arg), f.i = 0, f.j = 0, f.ptr = NULL);
	if (flag == 1)
		f.ptr = ft_add_new_arg(&f);
	else if (flag == 0)
	{
		while (f.value[f.i] != '\0' && f.value[f.i] != '=')
			f.i++;
		if (f.value[f.i] == '=')
			f.i++;
		f.tmp = ft_strjoin(old_arg, f.value + f.i);
		ft_check_allocation(f.tmp);
		f.ptr = f.tmp;
	}
	return (f.ptr);
}

static int	ft_add_already_exits(char *arg, t_env *envp)
{
	t_env	*head;
	char	*tmp;
	int		i;

	i = 0;
	head = envp;
	while (arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
		i++;
	while (head != NULL)
	{
		if (ft_strncmp(arg, head->value, i) == 0)
		{
			if (!ft_strchr(arg, '+'))
				tmp = ft_strdup(arg);
			else
				tmp = ft_append_value(arg, head->value, 0);
			(1) && (free(head->value), head->value = NULL);
			if (!tmp)
				return (0);
			head->value = tmp;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static int	ft_add_new_env(char *arg, t_env *envp)
{
	char	*value;
	char	*tmp;

	value = ft_filter_arg(arg);
	if (!value)
		return (1);
	if (!ft_strchr(value, '+'))
	{
		if (ft_push_value(value, &envp) == 0)
			return (1);
	}
	else
	{
		tmp = ft_append_value(value, NULL, 1);
		if (ft_push_value(tmp, &envp) == 0)
			return (1);
	}
	free(value);
	value = NULL;
	return (0);
}

int	ft_export(char *arg, t_env *envp)
{
	int	i;
	int	count;

	(1) && (i = -1, count = 0);
	if (arg == NULL)
		return (ft_print_exported_variable(envp), 0);
	if (ft_check_syntax_export(arg) == true)
		return (1);
	if (ft_check_if_exists(arg, envp) == true)
	{
		if (ft_add_already_exits(arg, envp) == 0)
			return (1);
	}
	else
		if (ft_add_new_env(arg, envp) == 1)
			return (1);
	return (0);
}
