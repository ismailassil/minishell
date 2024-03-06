/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 15:54:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_arg_is_exist(t_env *env, char *var)
{
	t_env	*head;
	char	*ptr;
	int		i;
	int		flag;

	(1) && (head = env, i = 0, flag = 0, ptr = NULL);
	while (head != NULL)
	{
		i = 0;
		while (var[i] == head->value[i])
			i++;
		if (head->value[i] == '=' && !ft_check_if_chars_digit(var[i]))
		{
			flag = 1;
			break ;
		}
		head = head->next;
	}
	if (head)
		ptr = ft_allocate_for_var(flag, head->value, i);
	return (ptr);
}

static int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

static char	*ft_handle_expand(t_env *env, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		exp.quote = arg[i++];
	while (arg[i] != '\0')
	{
		if (arg[i] == exp.quote)
			i++;
		if (!arg[i])
			break ;
		if ((arg[i] == '$' || arg[i] == '\"') && exp.quote != '\'')
		{
			exp.expa = ft_arg_is_exist(env, arg + (i + 1));
			exp.s = exp.new_str;
			exp.new_str = ft_strjoin(exp.new_str, exp.expa);
			i += ft_surpass_chars(arg + (i + 1));
		}
		else
			ft_append_char(&exp.new_str, arg[i++]);
		if (arg[i] == '\0')
			break ;
	}
	return (exp.new_str);
}

void	ft_expand_argument(t_env *env, t_token **linked_list)
{
	t_token	*head;

	head = *linked_list;
	while (head != NULL)
	{
		if (ft_strchr(head->token, '$'))
			head->token = ft_handle_expand(env, head->token);
		head = head->next;
	}
}
