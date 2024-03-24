/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/24 21:56:52 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	Checks if the expanded variable exists in the env
*/
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
		while (var[i] == head->value[i] && var[i] != '=')
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

int	ft_expand_word_after_dollar(t_expand *exp, int *i, char *arg, t_env *env)
{
	if (exp->quote == '\'')
	{
		ft_append_char(&(exp->new_str), arg[(*i)++]);
		return (1);
	}
	if (ft_handle_irregulare_cases(exp, arg[(*i) + 1], i, env))
		return (1);
	exp->expa = ft_arg_is_exist(env, arg + (*i + 1));
	exp->s = exp->new_str;
	exp->new_str = ft_strjoin(exp->new_str, exp->expa);
	free(exp->s);
	return (0);
}

/*
*	This function expands the variables
*/
char	*ft_handle_expand(t_env *env, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0, exp.quote = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		(exp.quote = arg[i++]);
	while (arg[i] != '\0')
	{
		if ((arg[i] == '\'' || arg[i] == '\"'))
			ft_update_quote(arg, &i, &exp);
		else if (arg[i] && arg[i] != exp.quote && arg[i] != '$')
			ft_append_char(&exp.new_str, arg[i++]);
		else if (arg[i] && arg[i] == '$')
		{
			if (ft_expand_word_after_dollar(&exp, &i, arg, env))
				continue ;
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i])
			i++;
	}
	return (exp.new_str);
}

/*
*	This function expands the Variables from the env
*/
void	ft_expand_argument(t_env *env, t_token **linked_list)
{
	t_token	*head;
	char	*tmp;

	(1) && (head = *linked_list, tmp = NULL);
	while (head != NULL)
	{
		if (ft_strchr(head->token, '$'))
		{
			tmp = ft_handle_expand(env, head->token);
			free(head->token);
			head->token = NULL;
			head->token = tmp;
		}
		head = head->next;
	}
}
