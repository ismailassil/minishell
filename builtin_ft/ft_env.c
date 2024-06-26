/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:41:44 by iassil            #+#    #+#             */
/*   Updated: 2024/04/29 13:39:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*ft_create_new_env(void)
{
	t_env	*envp;
	char	pwd[PATH_MAX];
	char	*tmp;

	envp = NULL;
	if (ft_push_value("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", \
		&envp) == 0)
		return (NULL);
	tmp = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
	if (!tmp)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	if (ft_push_value(tmp, &envp) == 0)
		return (NULL);
	(free(tmp), tmp = NULL);
	return (envp);
}

void	ft_add_shell_level(t_env *envp)
{
	t_shlvl	s;

	s.env = envp;
	s.flag = 0;
	while (s.env)
	{
		if (ft_strncmp(s.env->value, "SHLVL=", 6) == 0)
		{
			s.num = ft_atoi(s.env->value + 6) + 1;
			s.new_value = ft_itoa(s.num);
			free(s.env->value);
			s.tmp = ft_strjoin("SHLVL=", s.new_value);
			s.env->value = ft_strdup(s.tmp);
			(free(s.new_value), free(s.tmp));
			s.flag = 1;
			break ;
		}
		s.env = s.env->next;
	}
	if (s.flag == 0)
		if (ft_push_value("SHLVL=1", &envp) == 0)
			return ;
}

/*
*	This function transform the envir that comes with the process
*	to a linked list if they exist and do not exist
*/
t_struct	*ft_get_struct_and_env(char **env)
{
	t_struct	*strp;

	strp = malloc(sizeof(t_struct));
	ft_check_allocation(strp);
	strp->env = NULL;
	if (*env == NULL || env == NULL)
		strp->env = ft_create_new_env();
	else
	{
		while (*env)
		{
			if (ft_strncmp(*env, "_=", 2) == 0)
				env++;
			else
			{
				if (ft_push_value(*env, &strp->env) == 0)
					return (NULL);
				env++;
			}
		}
	}
	ft_add_shell_level(strp->env);
	strp->status = 0;
	return (strp);
}

void	ft_env(t_env *envp)
{
	while (envp != NULL)
	{
		if (ft_strchr(envp->value, '='))
			printf("%s\n", envp->value);
		envp = envp->next;
	}
}
