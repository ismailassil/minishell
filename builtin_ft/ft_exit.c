/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:16:54 by iassil            #+#    #+#             */
/*   Updated: 2024/04/02 01:07:24 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_contain_num(char *str)
{
	int	i;

	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_exit(t_cont *cont, t_struct *strp)
{
	int	i;
	int	a;

	i = 0;
	if (ft_arg_len(cont->arg) >= 2 && ft_contain_num(cont->arg[0]))
	{
		ft_error("exit\nmsh: exit: too many arguments\n");
		strp->status = 1;
	}
	else if (!ft_contain_num(cont->arg[0]))
	{
		(ft_error("exit\nmsh: exit: "), ft_error(cont->arg[0]));
		ft_error(": numeric argument required\n");
		exit(255);
	}
	else if (cont->arg[0])
	{
		ft_error("exit\n");
		a = ft_atoi(cont->arg[0]);
		exit(a % 256);
	}
	else
		(ft_error("exit\n"), exit(strp->status));
}
