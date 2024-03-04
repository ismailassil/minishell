/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:34:45 by iassil            #+#    #+#             */
/*   Updated: 2024/03/04 10:25:07 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env *envp, char *argument)
{
	t_env	*head;
	t_env	*lastnode;
	t_env	*tmp;

	head = envp;
	lastnode = head;
	while (head != NULL)
	{
		if (ft_strncmp(argument, head->value, ft_strlen(argument)) == 0)
		{
			tmp = head;
			lastnode->next = head->next;
			free(tmp);
			tmp = NULL;
			break ;
		}
		lastnode = head;
		head = head->next;
	}
}

// int main(int ac, char **av, char **env)
// {
// 	t_env	*envp;
// 	t_env	*head;

// 	envp = ft_check_env(env);
// 	head = envp;
// 	printf(YELLOW"=====Before=====\n"RESET);
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// 	printf(YELLOW"\n=====After=====\n"RESET);
// 	ft_unset(envp, av[1]);
// 	head = envp;
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// }
