/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlin_utils_v3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:52:12 by iassil            #+#    #+#             */
/*   Updated: 2024/04/27 23:37:39 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_rest(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && str[i] != '\0')
		{
			ft_putstr("=\"", 1);
			i++;
			flag = 1;
			break ;
		}
		else
			write(1, &str[i], 1);
	}
	if (flag == 1)
	{
		ft_putstr(str + i, 1);
		ft_putstr("\"", 1);
		flag = 0;
	}
	ft_putstr("\n", 1);
}

char	*get_env(t_env *env, char *str)
{
	t_env	*envp;

	envp = env;
	while (envp)
	{
		if (ft_strncmp(envp->value, str, ft_strlen(str)) == 0)
			return (envp->value + ft_strlen(str) + 1);
		envp = envp->next;
	}
	return (NULL);
}
