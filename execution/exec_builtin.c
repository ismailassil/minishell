/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/17 16:59:43 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_echo(t_cont *cont)
{
	int	n;
	int	i;

	(1) && (n = 0, i = 0);
	if (cont->arg &&
		ft_strncmp(cont->arg[0], "-n", ft_strlen(cont->arg[0])) == 0)
	{
		n = 1;
		cont->arg++;
	}
	while (cont->arg[i] != 0)
	{
		ft_echo(cont->arg[i]);
		i++;
		if (cont->arg[i])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}

static void	execute_cd(t_cont *cont, t_env **envp)
{
	if (cont->arg)
		ft_cd(cont->arg[0], envp);
	else
		ft_cd(NULL, envp);
}

int	ft_check_commands(t_cont *cont, t_env *env)
{
	char	*cmd;

	cmd = cont->cmd;
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (execute_echo(cont), 1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (execute_cd(cont, &env), 1);
	return (0);
}
