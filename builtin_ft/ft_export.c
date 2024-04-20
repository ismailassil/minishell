/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:07 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 12:39:57 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_check_if_exists(char *arg, t_env *envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = envp;
	while (arg && arg[i] != '\0' && arg[i] != '=' && arg[i] != '+')
		i++;
	while (head != NULL)
	{
		if (ft_strncmp(arg, head->value, i) == 0)
			return (true);
		head = head->next;
	}
	return (false);
}

static char	*ft_append_value(char *arg, char **old_arg, int flag)
{
	t_append_export	f;

	(1) && (f.value = arg, f.i = 0, f.j = 0, f.ptr = NULL);
	if (flag == 1)
		f.ptr = ft_add_new_arg(&f);
	else if (flag == 0)
	{
		while (f.value[f.i] != '\0' && f.value[f.i] != '=')
			f.i++;
		if (f.value[f.i] == '=')
			f.i++;
		if (!ft_strchr(*old_arg, '=')
			&& *old_arg[ft_strlen(*old_arg) - 1] != '=')
		{
			f.tmp1 = ft_strjoin(*old_arg, "=");
			ft_check_allocation(f.tmp1);
			free(*old_arg);
			*old_arg = ft_strdup(f.tmp1);
			ft_check_allocation(*old_arg);
			free(f.tmp1);
		}
		f.ptr = ft_strjoin(*old_arg, f.value + f.i);
		ft_check_allocation(f.ptr);
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
				tmp = ft_append_value(arg, &head->value, 0);
			(1) && (free(head->value), head->value = NULL);
			if (!tmp)
				return (0);
			head->value = ft_strdup(tmp);
			return (free(tmp), tmp = NULL, 1);
		}
		head = head->next;
	}
	return (0);
}

static int	ft_add_new_env(char *arg, t_env *envp)
{
	char	*tmp;

	if (!ft_strchr(arg, '+'))
	{
		if (ft_push_value(arg, &envp) == 0)
			return (1);
	}
	else
	{
		tmp = ft_append_value(arg, NULL, 1);
		if (ft_push_value(tmp, &envp) == 0)
			return (free(tmp), tmp = NULL, 1);
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int	ft_export(char *arg, t_struct *strp)
{
	int	i;
	int	count;

	(1) && (i = -1, count = 0);
	if (arg && arg[0] == '\0')
	{
		(ft_error("msh: export: \'"), ft_error(arg));
		ft_error("\': not a valid identifier\n");
		return (strp->status = 1, 1);
	}
	if (arg == NULL || arg[0] == '\0')
		return (ft_print_exported_variable(strp->env), 0);
	if (ft_check_syntax_export(arg) == true)
		return (strp->status = 1, 1);
	if (ft_check_if_exists(arg, strp->env) == true)
	{
		if (ft_add_already_exits(arg, strp->env) == 0)
			return (1);
	}
	else
		if (ft_add_new_env(arg, strp->env) == 1)
			return (1);
	return (0);
}
