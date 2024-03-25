/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:34:45 by iassil            #+#    #+#             */
/*   Updated: 2024/03/25 00:17:23 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (1);
	if (ft_isalpha(arg[0]) == 0)
	{
		(ft_error("msh: unset: "), ft_error(arg));
		ft_error(": not a valid identifier\n");
		return (true);
	}
	while (arg && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]))
		{
			(ft_error("msh: unset: "), ft_error(arg));
			ft_error(": not a valid identifier\n");
			return (true);
		}
		i++;
	}
	return (1);
}

void	ft_unset(t_env *envp, char *argument)
{
	t_env	*head;
	t_env	*lastnode;
	t_env	*tmp;

	(1) && (head = envp, lastnode = head);
	if (argument == NULL)
		return ;
	if (ft_check_arg(argument) == 0)
	{
		envp->status = 1;
		exit(FAIL);
	}
	while (head != NULL)
	{
		if (ft_strncmp(argument, head->value, ft_strlen(argument)) == 0)
		{
			(1) && (tmp = head, lastnode->next = head->next);
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			tmp = NULL;
			break ;
		}
		(1) && (lastnode = head, head = head->next);
	}
}

// void	v(void)
// {
// 	system("leaks unset");
// }

// int main(int ac, char **av, char **env)
// {
// 	t_env	*envp;
// 	t_env	*head;

// 	atexit(v);
// 	envp = ft_get_env(env);
// 	head = envp;
// 	printf(YELLOW"=====Before=====\n"RESET);
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// 	printf(YELLOW"\n=====After=====\n"RESET);
// 	ft_unset(envp, av[1]);
// 	head = envp;
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// 	ft_free_env(&envp);
// }
