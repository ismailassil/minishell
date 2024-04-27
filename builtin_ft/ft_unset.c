/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:34:45 by iassil            #+#    #+#             */
/*   Updated: 2024/04/27 21:25:16 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_arg(char *arg, t_struct **strp)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == '\0')
		return (1);
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
	{
		(ft_error("msh: unset: \'"), ft_error(arg));
		ft_error("\': not a valid identifier\n");
		return ((*strp)->status = 1, 1);
	}
	while (arg && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			(ft_error("msh: unset: \'"), ft_error(arg));
			ft_error("\': not a valid identifier\n");
			return ((*strp)->status = 1, 1);
		}
		i++;
	}
	if (arg && arg[0] == '_' && arg[1] == '\0')
		return (1);
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

void	ft_unset(t_struct **strp, char *arg)
{
	t_env	*head;
	t_env	*previous_node;
	int		i;

	(1) && (i = 0, head = (*strp)->env, previous_node = NULL);
	if (ft_check_arg(arg, strp) == 1)
		return ;
	while (head != NULL && head->value)
	{
		i = 0;
		while (head->value[i] != '\0' && head->value[i] != '='
			&& head->value[i] == arg[i])
			i++;
		if ((head->value[i] && head->value[i] == '=' && arg[i] == '\0')
			|| (head->value[i] == '\0' && arg[i] == '\0'))
		{
			ft_del_node(&head, &previous_node, strp);
			return ;
		}
		(1) && (previous_node = head, head = head->next);
	}
}
