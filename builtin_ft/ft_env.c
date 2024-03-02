/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:41:44 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 20:30:16 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_check_env(char **env)
{
	char	pwd[PATH_MAX];
	char	**envp;

	if (*env == NULL || env == NULL)
	{
		getcwd(pwd, sizeof(pwd));
		envp = (char **)malloc((3 * sizeof(char *)));
		if (!envp)
			return (write(2, "Error: Allocation failed\n", 25), NULL);
		envp[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		if (!envp[0])
			return (write(2, "Error: Allocation failed\n", 25), NULL);
		envp[1] = ft_strjoin("PWD=", pwd);
		if (!envp[1])
			return (write(2, "Error: Allocation failed\n", 25), NULL);
		envp[2] = NULL;
		return (envp);
	}
	return (env);
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
