/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:41:44 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 17:07:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*ft_create_new_env(void)
{
	t_env	*envp;
	char	pwd[PATH_MAX];
	char	*tmp;

	getcwd(pwd, sizeof(pwd));
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

t_env	*ft_get_env(char **env)
{
	t_env	*envp;

	envp = NULL;
	if (*env == NULL || env == NULL)
		envp = ft_create_new_env();
	else
	{
		while (*env)
		{
			if (ft_push_value(*env, &envp) == 0)
				return (NULL);
			env++;
		}
	}
	return (envp);
}

void	ft_env(t_env *envp)
{
	while (envp != NULL)
	{
		printf("%s\n", envp->value);
		envp = envp->next;
	}
}

// void	v(void)
// {
// 	system("leaks env");
// }

// int main(int ac, char **av, char **env)
// {
// 	t_env	*envp;

// 	// atexit(v);
// 	envp = ft_get_env(env);
// 	ft_env(envp);
// 	ft_free_env(&envp);
// }