/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 18:09:16 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_commands(t_cont *cont, t_env *env)
{
	char	*cmd;

	cmd = cont->cmd;
	if (cmd == NULL)
		return (env->status = 0, 1);
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (execute_echo(cont, &env), 1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (execute_cd(cont, &env), 1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (execute_env(cont, &env), 1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (execute_export(cont, &env), 1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (ft_pwd(env), 1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (execute_unset(cont, &env), 1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (ft_exit(), 1);
	return (0);
}
