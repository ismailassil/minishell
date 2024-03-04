/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:41:44 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 19:44:54 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_check_env(char **env)
{
	char	pwd[PATH_MAX];
	t_env	*envp;

	envp = NULL;
	if (*env == NULL || env == NULL)
	{
		getcwd(pwd, sizeof(pwd));
		if (ft_push_value("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", \
			&envp) == 0)
			return (NULL);
		if (ft_push_value(ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd))), \
			&envp) == 0)
			return (NULL);
		return (envp);
	}
	else
	{
		while (*env)
		{
			if (ft_push_value(*env, &envp) == 0)
				return (NULL);
			env++;
		}
		return (envp);
	}
}

void	ft_env(t_env *envp)
{
	while (envp)
	{
		printf("%s\n", envp->value);
		envp++;
	}
}
