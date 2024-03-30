/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:10:11 by iassil            #+#    #+#             */
/*   Updated: 2024/03/30 02:17:03 by iassil           ###   ########.fr       */
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
	if (cont->arg == NULL || cont->arg[0] == 0 || cont->arg[0][0] == '\0')
		(ft_add_path_executed_cmd("echo", (*strp)->env), write(1, "\n", 1));
	else
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
	(*strp)->status = 0;
}

/*
*	This function execute "cd"
*/
void	execute_cd(t_cont *cont, t_struct **strp)
{
	int	i;

	i = 0;
	if (cont->arg != NULL && cont->arg[0] != 0)
	{
		ft_cd(cont->arg[0], strp);
		while (cont->arg[i] != 0)
			i++;
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
	}
	else
	{
		ft_cd(NULL, strp);
		ft_add_path_executed_cmd("cd", (*strp)->env);
	}
}

/*
*	This function execute "env"
*/
void	execute_env(t_cont *cont, t_struct **strp)
{
	int	i;

	i = 0;
	if (cont->arg && cont->arg[0])
	{
		write(2, "msh: env: ", 10);
		(ft_error(cont->arg[0]), ft_error(": No such file or directory\n"));
		(*strp)->status = 127;
		while (cont->arg[i] != 0)
			i++;
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
	}
	else
	{
		ft_add_path_executed_cmd("env", (*strp)->env);
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
	(*strp)->status = 0;
	if (cont->arg == NULL || cont->arg[0] == NULL)
	{
		ft_export(NULL, *strp);
		ft_add_path_executed_cmd("export", (*strp)->env);
	}
	else
	{
		while (cont->arg && cont->arg[i] != 0)
			(1) && (ft_export(cont->arg[i], *strp), i++);
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
	}
}

/*
*	This function execute "unset"
*/
void	execute_unset(t_cont *cont, t_struct **strp)
{
	int		i;
	t_env	*envp;

	(1) && (i = 0, (*strp)->status = 0, envp = (*strp)->env);
	while (cont->arg && cont->arg[i] != 0)
		(1) && (ft_unset(strp, cont->arg[i]), i++);
	if (cont->arg == NULL || cont->arg[0] == 0)
		ft_add_path_executed_cmd("unset", (*strp)->env);
	else
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
}
