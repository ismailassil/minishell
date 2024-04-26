/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils_v2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:48:15 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 12:41:16 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				(ft_quotes_wildcard(&c->arg[i]), ft_export(c->arg[i], *strp)),
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

	ft_skip_null_args(cont);
	(1) && (i = 0, (*strp)->status = 0, envp = (*strp)->env);
	while (cont->arg && cont->arg[i] != 0)
		(1) && (ft_unset(strp, cont->arg[i]), i++);
	if (cont->arg == NULL || cont->arg[0] == 0)
		ft_add_path_executed_cmd("unset", (*strp)->env);
	else
		ft_add_path_executed_cmd(cont->arg[i - 1], (*strp)->env);
}
