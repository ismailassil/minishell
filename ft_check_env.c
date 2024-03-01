/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:00:12 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 21:00:22 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_env(char **env)
{
	char	pwd[PATH_MAX];
	char	**envp;

	if (env != NULL)
	{
		getcwd(pwd, sizeof(pwd));
		envp = (char **)malloc((2 * sizeof(char *)) + 1);
		if (!envp)
			return (NULL);
		envp[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
		if (!envp[0])
			return (NULL);
		envp[1] = ft_strjoin("PWD=", pwd);
		if (!envp[1])
			return (NULL);
		envp[2] = NULL;
		return (envp);
	}
	return (env);
}
