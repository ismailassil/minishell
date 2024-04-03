/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:16:54 by iassil            #+#    #+#             */
/*   Updated: 2024/04/03 02:48:08 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

unsigned long long	ft__atoi(const char *str)
{
	int						i;
	int						l;
	unsigned long long int	res;
	int						sign;

	i = 0;
	sign = 1;
	l = ft_strlen(str);
	while (str && is_space(str[i]))
		i++;
	res = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (ft_isdigit(str[i]))
	{
		res = (10 * res) + (str[i] - '0');
		if ((sign == 1) && (res > __LONG_MAX__))
			return (9223372036854775808ULL);
		if ((sign == -1) && (res > 9223372036854775808ULL))
			return (9223372036854775809ULL);
		i++;
	}
	return (res);
}

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

void	num_after_exit(t_cont *cont)
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
		num_after_exit(cont);
	else
		(ft_error("exit\n"), exit(strp->status));
}
