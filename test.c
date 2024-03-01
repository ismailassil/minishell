/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:12:02 by iassil            #+#    #+#             */
/*   Updated: 2024/03/01 20:42:49 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <string.h>

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

int main(int ac, char **av, char **env)
{
	char **envp = ft_check_env(env);
	if (envp == NULL)
		return (-1);
	int	i = 0;
	while (envp[i] != 0)
		puts(envp[i++]);
}
