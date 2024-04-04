/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:16:54 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 00:36:58 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_contain_num(char *str)
{
	int	i;

	i = 0;
	while (str && ft_strchr(" \t\n\v\f\r", str[i]))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str && str[i] && !ft_strchr(" \t\n\v\f\r", str[i]))
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

void	ft_num_after_exit(t_cont *cont)
{
	unsigned long long	a;
	int					sign;

	sign = 1;
	if (cont->arg[0][0] == '-')
		sign = -1;
	a = ft__atoi(cont->arg[0]);
	if (((sign == 1) && a > __LONG_MAX__)
		|| ((sign == -1) && a > 9223372036854775808UL))
	{
		(ft_error("exit\nmsh: exit: "), ft_error(cont->arg[0]));
		ft_error(MS);
		exit(255);
	}
	else
	{
		ft_error("exit\n");
		exit(((int)a * sign) % 256);
	}
}

void	ft_exit(t_cont *cont, t_struct *strp)
{
	if (ft_arg_len(cont->arg) >= 2 && ft_contain_num(cont->arg[0]))
	{
		ft_error("exit\nmsh: exit: too many arguments\n");
		strp->status = 1;
	}
	else if (!ft_contain_num(cont->arg[0]))
	{
		(ft_error("exit\nmsh: exit: "), ft_error(cont->arg[0]), ft_error(MS));
		exit(255);
	}
	else if (cont->arg[0] && ft_contain_num(cont->arg[0]))
		ft_num_after_exit(cont);
	else
		(ft_error("exit\n"), exit(strp->status));
}
