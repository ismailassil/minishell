/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_v1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:42:41 by iassil            #+#    #+#             */
/*   Updated: 2024/04/03 00:33:49 by iassil           ###   ########.fr       */
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
		free(return_path);
	}
	return (NULL);
}

static char	*ft_check_path(char *cmd, t_struct *strp, t_cont *cont)
{
	t_path	f;

	f.head = strp->env;
	while (f.head != NULL)
	{
		f.envp_path = ft_strnstr(f.head->value, "PATH=", 5);
		f.head = f.head->next;
		if (f.envp_path != NULL)
			break ;
	}
	if (f.envp_path == NULL)
		(perror("path"), ft_exitf(&strp, &cont), free(strp), exit(FAIL));
	f.return_path = ft_strtrim(f.envp_path, "PATH=");
	if (f.return_path == NULL)
		(ft_exitf(&strp, &cont), free(strp), exit(FAIL));
	f.path = ft_split(f.return_path, ':');
	if (f.path == NULL)
		(ft_f(f.path), ft_exitf(&strp, &cont), free(strp), exit(FAIL));
	(free(f.return_path), f.return_path = NULL);
	f.envp_path = ft_trim_path(f.path, cmd);
	if (!f.envp_path)
		(ft_return_path(f.path, cmd, strp, cont), exit(127));
	return (f.envp_path);
}

void	ft_check_(char **envp_path, char *cmd, t_struct *strp, t_cont *cont)
{
	if (cmd && (cmd[0] == '\0'
			|| (cmd[0] == '.' && (cmd[1] == '\0' || cmd[1] == '.'))))
	{
		if (cmd && cmd[0] == '.' && cmd[1] == '\0')
		{
			ft_error("msh: .: filename argument required\n");
			ft_error(".: usage: . filename [arguments]\n");
			exit(2);
		}
		else
			(ft_stat(cmd, ": command not found\n", strp, cont), exit(127));
	}
	if (ft_find_slash_or_point(cmd) == 1)
		ft_check_path_cmd(envp_path, cmd, strp, cont);
	else
	{
		*envp_path = ft_check_path(cmd, strp, cont);
		if (*envp_path == NULL)
			(ft_exitf(&strp, &cont), free(strp), exit(FAIL));
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
	if (cont->cmd[0] == '.')
		i++;
	if (cont->cmd != NULL)
		argv[j++] = ft_strdup(cont->cmd + i);
	i = 0;
	while (cont->arg && cont->arg[i] != 0)
	{
		argv[j] = ft_strdup(cont->arg[i]);
		ft_check_allocation(argv[j]);
		(1) && (i++, j++);
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
