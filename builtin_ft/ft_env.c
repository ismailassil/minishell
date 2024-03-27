/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:41:44 by iassil            #+#    #+#             */
/*   Updated: 2024/03/27 20:22:23 by iassil           ###   ########.fr       */
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
		(write(2, "Error: Allocation failed\n", 19), exit(FAIL));
	if (ft_push_value(tmp, &envp) == 0)
		return (NULL);
	(free(tmp), tmp = NULL);
	return (envp);
}

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
			if (ft_push_value(*env, &strp->env) == 0)
				return (NULL);
			env++;
		}
	}
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
