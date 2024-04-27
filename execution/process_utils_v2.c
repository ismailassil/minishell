/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:09:46 by iassil            #+#    #+#             */
/*   Updated: 2024/04/27 23:34:01 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

static void	ft_fill_argv(t_cont *cont, char ***argv, int *j)
{
	int	i;

	i = 0;
	while (cont->arg && cont->arg[i] != 0)
	{
		if (ft_evar(cont->arg_is_var[i], \
			cont->arg_is_quote[i], cont->arg[i]))
			i++;
		else
		{
			(*argv)[*j] = ft_strdup(cont->arg[i]);
			ft_check_allocation((*argv)[*j]);
			(1) && ((*j)++, i++);
		}
	}
	(*argv)[*j] = 0;
}

char	**ft_join_for_argv_execve(t_cont *cont)
{
	char	**argv;
	int		count;
	int		i;
	int		j;

	(1) && (i = 0, j = 0, count = 0);
	argv = NULL;
	while (cont->arg && cont->arg[i] != 0)
	{
		if (ft_evar(cont->arg_is_var[i], \
			cont->arg_is_quote[i], cont->arg[i]))
			i++;
		else
			(1) && (i++, count++);
	}
	argv = malloc((count + 2) * sizeof(char *));
	ft_check_allocation(argv);
	i = 0;
	if (cont->cmd && cont->cmd[0] == '.')
		i++;
	if (cont->cmd != NULL)
		argv[j++] = ft_strdup(cont->cmd + i);
	ft_fill_argv(cont, &argv, &j);
	return (argv);
}

char	*ft_remove_slash(char **cmd)
{
	int		len;
	char	*ptr;

	len = ft_strlen(*cmd);
	if (len != 0 && (*cmd)[len - 1] == '/')
	{
		ptr = ft_substr(*cmd, 0, len - 1);
		ft_check_allocation(ptr);
	}
	else
	{
		ptr = ft_strdup(*cmd);
		ft_check_allocation(ptr);
	}
	return (ptr);
}

void	ft_check_rest(char *cmd, t_struct *strp,
			t_cont *cont, struct stat file_stat)
{
	char	*ptr;

	ptr = ft_remove_slash(&cmd);
	if (access(ptr, F_OK) == 0 && S_ISREG(file_stat.st_mode) == 0)
	{
		free(ptr);
		ft_stat(cmd, ": Not a directory\n", strp, cont);
		exit(126);
	}
	else
	{
		free(ptr);
		ft_stat(cmd, ": No such file or directory\n", strp, cont);
		exit(127);
	}
}

void	ft_check_path_cmd(char **envp_path, char *cmd,
			t_struct *strp, t_cont *cont)
{
	struct stat	file_stat;

	stat(cmd, &file_stat);
	if (access(cmd, F_OK) == 0 && stat(cmd, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode) && access(cmd, F_OK | X_OK))
			(ft_stat(cmd, ": Permission denied\n", strp, cont), exit(126));
		if (S_ISREG(file_stat.st_mode) && !access(cmd, X_OK)
			&& file_stat.st_size == 0)
			exit(SUCCESS);
		if (S_ISREG(file_stat.st_mode))
			*envp_path = ft_strdup(cmd);
		else if (S_ISDIR(file_stat.st_mode))
			(ft_stat(cmd, ": is a directory\n", strp, cont), exit(126));
		else
			(ft_stat(cmd, ": command not found\n", strp, cont), exit(127));
	}
	else
		ft_check_rest(cmd, strp, cont, file_stat);
}
