/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/12 17:07:26 by musashi          ###   ########.fr       */
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

/*
*	Define the quote,
*	that should not be included within the string
*/
void	ft_update_quote(char *arg, int *i, t_expand *exp)
{
	if (exp->quote == arg[*i])
	{
		exp->quote = 0;
		(*i)++;
	}
	else if (!exp->quote)
	{
		exp->quote = arg[*i];
		(*i)++;
	}
	else
	{
		ft_append_char(&exp->new_str, arg[*i]);
		(*i)++;
	}
}

static void	ft_handle_rest(t_env *env, t_expand	exp, char *arg, int *i)
{
	exp.expa = ft_arg_is_exist(env, arg + (*i + 1));
	exp.s = exp.new_str;
	exp.new_str = ft_strjoin(exp.new_str, exp.expa);
	i += ft_surpass_chars(arg + (*i + 1));
}

/*
*	This function expands the variables
*/
static char	*ft_handle_expand(t_env *env, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0);
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
			if (exp.quote == '\'')
			{
				ft_append_char(&exp.new_str, arg[i++]);
				continue ;
			}
			if (ft_handle_inregulare_cases(&exp, arg[i + 1], &i))
				continue ;
			ft_handle_rest(env, exp, arg, &i);
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

	head = *linked_list;
	while (head != NULL)
	{
		if (ft_strchr(head->token, '$'))
			head->token = ft_handle_expand(env, head->token);
		head = head->next;
	}
}
