/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 00:51:08 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_compare_arg(char *cmd, t_cont *cont, t_env *env, int *flag)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		(1) && (execute_echo(cont, &env), *flag = 1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		(1) && (execute_cd(cont, &env), *flag = 1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		(1) && (execute_env(cont, &env), *flag = 1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		(1) && (execute_export(cont, &env), *flag = 1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		(1) && (ft_pwd(env), *flag = 1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		(1) && (execute_unset(cont, &env), *flag = 1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		(1) && (ft_exit(), *flag = 1);
}

int	ft_check_commands(t_cont *cont, t_env *env, t_info *info, int j)
{
	char	*cmd;
	int		flag;
	int		original_stdout;

	(1) && (cmd = cont->cmd, flag = 0);
	if (cmd == NULL)
		return (env->status = 0, 1);
	if (j == 1 && info->nbr_cont == 1 && info->fd.outfile != 1)
	{
		original_stdout = dup(STDOUT_FILENO);
		ft_syscall(dup2(info->fd.outfile, STDOUT_FILENO), "dup2");
		ft_syscall(close(info->fd.outfile), "close");
	}
	ft_compare_arg(cmd, cont, env, &flag);
	if (j == 1 && flag == 1 && info->nbr_cont == 1 && info->fd.outfile != 1)
	{
		ft_syscall(dup2(original_stdout, STDOUT_FILENO), "dup2");
		ft_syscall(close(original_stdout), "close");
		return (1);
	}
	else if (flag == 1)
		return (1);
	return (0);
}
