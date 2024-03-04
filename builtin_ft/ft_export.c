/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/04 10:59:33 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	export string"s"=value		==>	strings=value
*	export hello=				==>	hello=
*	export string				==>	'\0'
*/

bool	ft_check_argument_validity(char *argument)
{
	int	i;

	i = 0;
	while (argument[i] != '\0')
		if (argument[i++] == '=')
			return (false);
	return (true);
}

bool	ft_check_if_exists(char *argument, t_env *envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = envp;
	while (argument[i] != '\0' && argument[i] != '=')
		i++;
	while (head != NULL)
	{
		if (ft_strncmp(argument, head->value, i) == 0)
			return (true);
		head = head->next;
	}
	return (false);
}

int	ft_add_already_exits(char *argument, t_env *envp)
{
	t_env	*head;
	char	*tmp;
	int		i;

	i = 0;
	head = envp;
	while (argument[i] != '\0' && argument[i] != '=')
		i++;
	while (head != NULL)
	{
		if (ft_strncmp(argument, head->value, i) == 0)
		{
			free(head->value);
			head->value = ft_strdup(argument);
			if (!head->value)
				return (1);
		}
		head = head->next;
	}
	return (0);
}

char	*ft_filter_argument(char *argument, t_env *envp)
{
	char	*value;
	int		i;
	int		j;
	int		count;

	(1) && (i = 0, count = 0);
	while (argument[i] != '\0')
	{
		if (argument[i] == '\"' || argument[i] == '\"')
			count++;
		i++;
	}
	value = (char *)malloc((i - count + 1) * sizeof(char));
	if (!value)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (argument[i] != '\0')
	{
		if (argument[i] == '\"' || argument[i] == '\'')
			i++;
		else
			(1) && (value[j] = argument[i], i++, j++);
	}
	value[j] = '\0';
	return (value);
}

int	ft_add_new_env(char *argument, t_env *envp)
{
	char	*value;

	value = ft_filter_argument(argument, envp);
	if (!value)
		return (1);
	if (ft_push_value(value, &envp) == 0)
		return (1);
	return (0);
}

int	ft_export(char *argument, t_env *envp)
{
	int		i;

	i = 0;
	if (argument == NULL)
		return (0);
	if (ft_check_argument_validity(argument) == true)
		return (1);
	if (ft_check_if_exists(argument, envp) == true)
	{
		if (ft_add_already_exits(argument, envp) == 0)
			return (1);
	}
	else
		if (ft_add_new_env(argument, envp) == 1)
			return (1);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_env	*envp;
// 	t_env	*head;

// 	envp = ft_check_env(env);
// 	printf(YELLOW"=====Before=====\n"RESET);
// 	head = envp;
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// 	printf(YELLOW"\n=====After=====\n"RESET);
// 	if (ft_export(av[1], envp) == 1)
// 		(printf("Error\n"), exit(1));
// 	head = envp;
// 	while (head)
// 		(1) && (printf("%s\n", head->value), head = head->next);
// }
