/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils_v1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:10:11 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 12:45:59 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_new_ptr(t_cont *cont, char ***ptr)
{
	int	i;
	int	len;

	(1) && (i = 0, len = 0);
	while (cont->arg && cont->arg[i])
	{
		if (cont->arg[i] && cont->arg_is_var[i] && cont->arg[i][0] == '\0')
			i++;
		else
		{
			(*ptr)[len] = ft_strdup(cont->arg[i++]);
			ft_check_allocation((*ptr)[len++]);
		}
	}
	(*ptr)[len] = 0;
}

void	ft_skip_null_args(t_cont *cont)
{
	int		i;
	int		len;
	char	**ptr;

	(1) && (i = 0, len = 0);
	if (!cont->arg[i])
		return ;
	while (cont->arg && cont->arg[i])
	{
		if (cont->arg[i] && cont->arg_is_var[i] && cont->arg[i][0] == '\0')
			i++;
		else
			(1) && (len++, i++);
	}
	ptr = malloc((len + 1) * sizeof(char *));
	ft_check_allocation(ptr);
	ft_fill_new_ptr(cont, &ptr);
	ft_f(cont->arg);
	cont->arg = ptr;
}

/*
*	This function execute "echo"
*/
void	execute_echo(t_cont *cont, t_struct **strp)
{
	int	n;
	int	i;
	int	flag;

	(1) && (n = 0, i = 0, flag = 0);
	ft_skip_null_args(cont);
	if (cont->arg && cont->arg[i] && (ft_strncmp(cont->arg[i], "-n", 3) == 0
			|| ft_is_n(cont->arg[i])))
		(1) && (n = 1, i++);
	while (cont->arg && cont->arg[i] != 0)
	{
		flag = 1;
		ft_echo(cont->arg[i]);
		i++;
		if (cont->arg && cont->arg[i])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
	if (cont->arg == NULL || cont->arg[0] == 0 || cont->arg[0][0] == '\0')
		ft_add_path_executed_cmd("echo", (*strp)->env);
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
	ft_skip_null_args(cont);
	if (cont->arg == NULL || cont->arg[i] == 0)
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
