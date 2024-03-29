/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:10:11 by iassil            #+#    #+#             */
/*   Updated: 2024/03/29 02:56:30 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This function execute "echo"
*/
void	execute_echo(t_cont *cont, t_struct **strp)
{
	int	n;
	int	i;

	ft_add_path_executed_cmd("echo", (*strp)->env);
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
	if (n == 0 || cont->arg[0] == 0)
		write(1, "\n", 1);
	(*strp)->status = 0;
}

/*
*	This function execute "cd"
*/
void	execute_cd(t_cont *cont, t_struct **strp)
{
	ft_add_path_executed_cmd("cd", (*strp)->env);
	if (cont->arg)
		ft_cd(cont->arg[0], strp);
	else
		ft_cd(NULL, strp);
}

/*
*	This function execute "env"
*/
void	execute_env(t_cont *cont, t_struct **strp)
{
	ft_add_path_executed_cmd("env", (*strp)->env);
	if (cont->arg && cont->arg[0])
	{
		write(2, "env: ", 5);
		ft_error(cont->arg[0]);
		ft_error(": No such file or directory\n");
		(*strp)->status = 127;
	}
	else
	{
		ft_env(((*strp)->env));
		(*strp)->status = 0;
	}
}

/*
*	This function execute "export"
*/
void	execute_export(t_cont *cont, t_struct **strp)
{
	int	i;

	i = 0;
	ft_add_path_executed_cmd("export", (*strp)->env);
	(*strp)->status = 0;
	if (cont->arg[0] == NULL)
		ft_export(NULL, *strp);
	else
		while (cont->arg[i] != 0)
			(1) && (ft_export(cont->arg[i], *strp), i++);
}

/*
*	This function execute "unset"
*/
void	execute_unset(t_cont *cont, t_struct **strp)
{
	int		i;
	t_env	*envp;

	i = 0;
	ft_add_path_executed_cmd("unset", (*strp)->env);
	(*strp)->status = 0;
	envp = (*strp)->env;
	while (cont->arg && cont->arg[i] != 0)
		(1) && (ft_unset(strp, cont->arg[i]), i++);
}
