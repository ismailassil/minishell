/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:10:11 by iassil            #+#    #+#             */
/*   Updated: 2024/03/20 21:27:53 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_echo(t_cont *cont, t_env **envp)
{
	int	n;
	int	i;

	(1) && (n = 0, i = 0);
	if (cont->arg
		&& ft_strncmp(cont->arg[0], "-n", ft_strlen(cont->arg[0])) == 0)
	{
		n = 1;
		i++;
	}
	while (cont->arg[0] != 0 && cont->arg && cont->arg[i] != 0)
	{
		ft_echo(cont->arg[i]);
		i++;
		if (cont->arg && cont->arg[i])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
	(*envp)->status = 0;
}

void	execute_cd(t_cont *cont, t_env **envp)
{
	if (cont->arg)
		ft_cd(cont->arg[0], envp);
	else
		ft_cd(NULL, envp);
}

void	execute_env(t_cont *cont, t_env **envp)
{
	if (cont->arg && cont->arg[0])
	{
		write(2, "env: ", 5);
		ft_error(cont->arg[0]);
		ft_error(": No such file or directory\n");
		(*envp)->status = 127;
	}
	else
	{
		ft_env(*envp);
		(*envp)->status = 0;
	}
}

void	execute_export(t_cont *cont, t_env **envp)
{
	int	i;

	i = 0;
	if (cont->arg[0] == NULL)
		ft_export(NULL, *envp);
	else
		while (cont->arg[i] != 0)
			(1) && (ft_export(cont->arg[i], *envp), i++);
	(*envp)->status = 0;
}

void	execute_unset(t_cont *cont, t_env **envp)
{
	int	i;

	i = 0;
	while (cont->arg && cont->arg[i] != 0)
		(1) && (ft_unset(*envp, cont->arg[i]), i++);
	(*envp)->status = 0;
}
