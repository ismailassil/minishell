/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:10:11 by iassil            #+#    #+#             */
/*   Updated: 2024/04/06 02:59:55 by iassil           ###   ########.fr       */
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
	if (cont->arg == NULL || cont->arg[0] == NULL)
	{
		ft_cd(NULL, strp);
		ft_add_path_executed_cmd("cd", (*strp)->env);
		return ;
	}
	while (cont->arg && cont->arg[i])
	{
		if (ft_evar(cont->arg_is_var[i], \
			cont->arg_is_quote[i], cont->arg[i]))
			i++;
		else
			break ;
	}
	if (cont->arg[i])
		ft_cd(cont->arg[i], strp);
	if (cont->arg[i] == 0)
		ft_cd(NULL, strp);
	while (cont->arg[i])
		i++;
	ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
}

/*
*	This function execute "env"
*/
void	execute_env(t_cont *c, t_struct **strp)
{
	int	i;

	i = 0;
	while (c->arg && c->arg[i])
	{
		while (ft_evar(c->arg_is_var[i], c->arg_is_quote[i], c->arg[i]))
			i++;
		if (c->arg[i] != 0)
		{
			(ft_error("env: "), ft_error(c->arg[i]));
			ft_error(": No such file or directory\n");
			(*strp)->status = 127;
			while (c->arg && c->arg[i] != 0)
			{
				if (ft_evar(c->arg_is_var[i], c->arg_is_quote[i], c->arg[i]))
					i++;
				else
					(1) && (ft_add_path_executed_cmd(c->arg[i], \
						(*strp)->env), i++);
			}
			return ;
		}
	}
	ft_add_path_executed_cmd("env", (*strp)->env);
	(1) && (ft_env(((*strp)->env)), (*strp)->status = 0);
}

/*
*	This function execute "export"
*/
void	execute_export(t_cont *c, t_struct **strp)
{
	int	i;

	i = 0;
	(*strp)->status = 0;
	if (c->arg == NULL || c->arg[0] == NULL || (ft_evar(\
		c->arg_is_var[i], c->arg_is_quote[i], c->arg[i])
			&& !c->arg[i + 1]))
	{
		ft_export(NULL, *strp);
		ft_add_path_executed_cmd("export", (*strp)->env);
	}
	else
	{
		while (c->arg && c->arg[i] != 0)
		{
			if (ft_evar(c->arg_is_var[i], c->arg_is_quote[i], c->arg[i]))
				i++;
			else
			{
				ft_export(c->arg[i], *strp),
				ft_add_path_executed_cmd(c->arg[i], (*strp)->env);
				i++;
			}
		}
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
