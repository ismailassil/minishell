/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:48 by iassil            #+#    #+#             */
/*   Updated: 2024/03/25 18:42:40 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This file hold the functions that expand the variables passed to here_doc
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

static int	ft_expand_word_after_dollar_here_doc(t_expand *exp, int *i, \
	char *arg, t_struct *strp)
{
	if (ft_handle_irregulare_cases(exp, arg[(*i) + 1], i, strp))
		return (1);
	exp->expa = ft_arg_is_exist(strp->env, arg + (*i + 1));
	exp->s = exp->new_str;
	exp->new_str = ft_strjoin(exp->new_str, exp->expa);
	return (0);
}

/*
*	This function expands the variables for the here_doc
*/
char	*ft_handle_expand_for_here_doc(t_struct *strp, char *arg)
{
	int			i;
	t_expand	exp;

	(1) && (exp.new_str = NULL, i = 0);
	while (arg[i] != '\0')
	{
		if (arg[i] && arg[i] != '$')
			ft_append_char(&exp.new_str, arg[i++]);
		else if (arg[i] && arg[i] == '$')
		{
			if (ft_expand_word_after_dollar_here_doc(&exp, &i, arg, strp))
				continue ;
			i += ft_surpass_chars(arg + (i + 1));
		}
		else if (arg[i])
			i++;
	}
	return (exp.new_str);
}
