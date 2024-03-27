/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:34:45 by iassil            #+#    #+#             */
/*   Updated: 2024/03/27 20:22:31 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == '\0')
		return (1);
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
	{
		(ft_error("msh: unset: \'"), ft_error(arg));
		ft_error("\': not a valid identifier\n");
		return (1);
	}
	while (arg && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			(ft_error("msh: unset: \'"), ft_error(arg));
			ft_error("\': not a valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}
	
void	ft_del_node(t_env **env, t_env **previous_node, t_struct **strp)
{
	t_env	*tobefreed;

	tobefreed = *env;
	if (*previous_node == NULL)
	{
		*env = (*env)->next;
		(*strp)->env = *env;
	}
	else
	{
		*env = (*env)->next;
		(*previous_node)->next = (*env);
	}
	free(tobefreed->value);
	tobefreed->value = NULL;
	free(tobefreed);
	tobefreed = NULL;
}

void	ft_unset(t_struct **strp, char *argument)
{
	t_env	*head;
	t_env	*previous_node;
	int		i;

	(1) && (i = 0, head = (*strp)->env, previous_node = NULL);
	if (ft_check_arg(argument) == 1)
	{
		(*strp)->status = 1;
		return ;
	}
	while (head != NULL && head->value)
	{
		i = 0;
		while (head->value[i] != '\0' && head->value[i] != '='
			&& head->value[i] == argument[i])
			i++;
		if (head->value[i] != '\0' && head->value[i] == '=')
		{
			ft_del_node(&head, &previous_node, strp);
			return ;
		}
		previous_node = head;
		head = head->next;
	}
}
