/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:42:41 by iassil            #+#    #+#             */
/*   Updated: 2024/03/17 17:44:48 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_trim_path(char **path, char *cmd)
{
	size_t	i;
	char	*path_holder;
	char	*return_path;

	i = -1;
	path_holder = NULL;
	while (path[++i] != 0)
	{
		path_holder = ft_strjoin(path[i], "/");
		if (path_holder == NULL)
			(free(path_holder), path_holder = NULL, exit(FAIL));
		return_path = ft_strjoin(path_holder, cmd);
		if (return_path == NULL)
			(free(return_path), return_path = NULL,
				free(path_holder), path_holder = NULL,
				exit(FAIL));
		(free(path_holder), path_holder = NULL);
		if (access(return_path, F_OK | X_OK) == 0)
		{
			ft_f(path);
			return (return_path);
		}
	}
	return (NULL);
}

static char	*ft_check_path(char *cmd, t_env *env)
{
	char	**path;
	char	*envp_path;
	char	*return_path;

	while (env != NULL)
	{
		envp_path = ft_strnstr(env->value, "PATH=", 5);
		env = env->next;
		if (envp_path != NULL)
			break ;
	}
	if (envp_path == NULL)
		(perror("path"), exit(FAIL));
	return_path = ft_strtrim(envp_path, "PATH=");
	if (return_path == NULL)
		(exit(FAIL));
	path = ft_split(return_path, ':');
	if (path == NULL)
		(ft_f(path), exit(FAIL));
	(free(return_path), return_path = NULL);
	envp_path = ft_trim_path(path, cmd);
	if (!envp_path)
		(ft_f(path), ft_error("msh: command not found: "), ft_error(cmd),
		write(2, "\n", 1), exit(FAIL));
	return (envp_path);
}

void	ft_check_(char **envp_path, char *cmd, t_env *env)
{
	if (access(cmd, F_OK | X_OK) == 0)
		*envp_path = cmd;
	else
	{
		*envp_path = ft_check_path(cmd, env);
		if (*envp_path == NULL)
			exit(FAIL);
	}
}

char	**ft_join_for_argv_execve(t_cont *cont)
{
	char	**argv;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	argv = NULL;
	while (cont->arg && cont->arg[i] != 0)
		i++;
	argv = malloc((i + 2) * sizeof(char *));
	if (argv == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	i = 0;
	argv[j++] = ft_strdup(cont->cmd);
	while (cont->arg && cont->arg[i] != 0)
	{
		argv[j] = ft_strdup(cont->arg[i]);
		ft_check_allocation(argv[j]);
		i++;
		j++;
	}
	argv[j] = 0;
	return (argv);
}

char	**ft_join_for_envp_execve(t_env *env)
{
	char	**envp;
	size_t	len;
	int		i;

	(1) && (i = 0, envp = NULL, len = ft_t_env_len(env));
	envp = malloc((len + 1) * sizeof(char *));
	if (!envp)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	while (env != NULL)
	{
		envp[i] = ft_strdup(env->value);
		ft_check_allocation(envp[i]);
		(1) && (env = env->next, i++);
	}
	envp[i] = 0;
	return (envp);
}
