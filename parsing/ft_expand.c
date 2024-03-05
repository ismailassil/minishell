/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 10:59:53 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_chars_digit(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_arg_is_exist(t_env *env, char *var)
{
	char	*ptr;
	int		i;

	while (env != NULL)
	{
		i = 0;
		while (var[i] == env->value[i])
			i++;
		if (env->value[i] == '=' && !check_if_chars_digit(var[i]))
			break ;
		env = env->next;
	}
	if (env->value)
	{
		env->value += (i + 1);
		ptr = ft_strdup(env->value);
		if (!ptr)
			return (NULL);
		env->value -= (i + 1);
		return (ptr);
	}
	return (NULL);
}

int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

void	handle_echo(t_env *env, char *argument)
{
	int		i;
	int		flag;
	int		quote;
	char	*expanded;
	char	*container;

	i = 0;
	flag = 0;
	quote = 0;
	while (argument[i] == ' ')
		i++;
	if (argument[i] == '\'' || argument[i] == '\"')
		quote = argument[i++];
	while (argument[i])
	{
		if (argument[i] == quote)
			i++;
		if (!argument[i])
			break ;
		if (argument[i] == '$' && argument[i - 1] != '\'')
		{
			flag = 1;
			container = ft_substr(argument, 0, i);
			if (!container)
				(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			expanded = ft_arg_is_exist(env, argument + (i + 1));
			if (expanded != NULL)
				(i += ft_surpass_chars(argument + (i + 1)));
			else
			{
				expanded = ft_strjoin(container, expanded);
				if (!expanded)
					(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
			}
			if (!argument[i])
				break ;
			while (argument [i] && argument[i] == ' ' && argument[i + 1] == ' ')
				i++;
			if (argument[i] != quote)
			{
				if (quote == 0 && (argument[i] == '\'' || argument[i] == '\"'))
					;
				else
					printf("%c", argument[i]);
			}
			i++;
		}
	}
	if (flag == 0)
	{
		container = ft_strdup(argument);
		if (!container)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	}
}
